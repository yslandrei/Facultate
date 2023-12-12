package com.example.service;

import com.example.domain.*;
import com.example.domain.exceptions.EntityDoesNotExistException;
import com.example.repository.database.*;
import com.example.utils.observer.Observable;
import com.example.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

public class MessageService implements Observable {

    private final UserDatabaseRepository userRepository;

    private final FriendshipDatabaseRepository friendshipRepository;

    private final MessageDatabaseRepository messageRepository;

    private final MessageReceiverDatabaseRepository messageReceiverRepository;

    private List<Observer> observers = new ArrayList<>();

    public MessageService(UserDatabaseRepository userRepository, FriendshipDatabaseRepository friendshipRepository, MessageDatabaseRepository messageRepository, MessageReceiverDatabaseRepository messageReceiverRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.messageRepository = messageRepository;
        this.messageReceiverRepository = messageReceiverRepository;
    }

    public List<Message> getMessagesBetweenTwoUsers(Long id1, Long id2) {
        userRepository.findOne(id1)
                .orElseThrow(() -> new EntityDoesNotExistException(id1));
        userRepository.findOne(id2)
                .orElseThrow(() -> new EntityDoesNotExistException(id2));
        if (friendshipRepository.findOne(new Tuple<>(id1, id2)).isEmpty() && friendshipRepository.findOne(new Tuple<>(id2, id1)).isEmpty())
                throw new EntityDoesNotExistException(new Friendship(new Tuple<>(id1, id2)));

        List<Message> messages = new ArrayList<>();
        messageRepository.executeQuery("select * from messages" +
                " join messages_receivers on messages.id=messages_receivers.message_id" +
                " where (from_id=%d and to_id=%d) or (from_id=%d and to_id=%d)".formatted(id1, id2, id2, id1) +
                " order by date").forEach(messages::add);
        return messages;
    }

    public void sendMessage(Long fromId, List<Long> toIds, String message, Long replyId) {
        userRepository.findOne(fromId)
                .orElseThrow(() -> new EntityDoesNotExistException(fromId));
        toIds.forEach(toId -> {
            userRepository.findOne(toId)
                    .orElseThrow(() -> new EntityDoesNotExistException(toId));
            if (friendshipRepository.findOne(new Tuple<>(fromId, toId)).isEmpty() && friendshipRepository.findOne(new Tuple<>(toId, fromId)).isEmpty())
                throw new EntityDoesNotExistException(new Friendship(new Tuple<>(fromId, toId)));
        });

        Message msg = new Message(fromId, message, LocalDateTime.now().withNano(0), replyId);
        messageRepository.save(msg);
        // could be better (change repo to return the id of the saved entity)
        AtomicReference<Long> msgId = new AtomicReference<>(null);
        messageRepository.findAll().forEach(msgIter -> {
            if (msg.getFromId().equals(msgIter.getFromId()) && msg.getMessage().equals(msgIter.getMessage()) && msg.getDate().equals(msgIter.getDate()))
                msgId.set(msgIter.getId());
        });
        toIds.forEach(toId -> {
            MessageReceiver messageReceiver = new MessageReceiver(toId, msgId.get());
            messageReceiverRepository.save(messageReceiver);
        });
        notifyObservers();
    }

    public Message getMessageById(Long id) {
        return messageRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));
    }

    @Override
    public void addObserver(Observer e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers() {
        observers.forEach(x -> x.update());
    }
}
