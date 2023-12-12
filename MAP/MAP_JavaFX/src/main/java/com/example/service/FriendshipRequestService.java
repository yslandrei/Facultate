package com.example.service;

import com.example.domain.*;
import com.example.domain.exceptions.EntityAlreadyExistsException;
import com.example.domain.exceptions.EntityDoesNotExistException;
import com.example.repository.Repository;
import com.example.repository.database.FriendshipDatabaseRepository;
import com.example.repository.database.FriendshipRequestDatabaseRepository;
import com.example.repository.database.UserDatabaseRepository;
import com.example.utils.observer.Observable;
import com.example.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class FriendshipRequestService implements Observable {

    private final UserDatabaseRepository userRepository;

    private final FriendshipDatabaseRepository friendshipRepository;

    private final FriendshipRequestDatabaseRepository friendshipRequestRepository;

    private List<Observer> observers = new ArrayList<>();

    public FriendshipRequestService(UserDatabaseRepository userRepository, FriendshipDatabaseRepository friendshipRepository, FriendshipRequestDatabaseRepository friendshipRequestRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.friendshipRequestRepository = friendshipRequestRepository;
    }

    public void sendFriendRequest(Long fromId, Long toId) {
        User from = userRepository.findOne(fromId)
                .orElseThrow(() -> new EntityDoesNotExistException(fromId));
        User to = userRepository.findOne(toId)
                .orElseThrow(() -> new EntityDoesNotExistException(toId));

        FriendshipRequest friendshipRequest = new FriendshipRequest(new Tuple<>(fromId, toId), FriendshipRequestStatus.PENDING);
        Optional<FriendshipRequest> optionalFriendshipRequest = friendshipRequestRepository.save(friendshipRequest);
        if (optionalFriendshipRequest.isPresent()) {
            if (optionalFriendshipRequest.get().getStatus() == FriendshipRequestStatus.REJECTED)
                friendshipRequestRepository.update(friendshipRequest);
            else throw new EntityAlreadyExistsException(friendshipRequest);
        }

        notifyObservers();
    }

    public void acceptFriendRequest(Long fromId, Long toId) {
        User from = userRepository.findOne(fromId)
                .orElseThrow(() -> new EntityDoesNotExistException(fromId));
        User to = userRepository.findOne(toId)
                .orElseThrow(() -> new EntityDoesNotExistException(toId));

        FriendshipRequest friendshipRequest = friendshipRequestRepository.findOne(new Tuple<>(fromId, toId))
                .orElseThrow(() -> new EntityDoesNotExistException(new FriendshipRequest(new Tuple<>(fromId, toId), FriendshipRequestStatus.PENDING)));

        if (friendshipRequest.getStatus() != FriendshipRequestStatus.PENDING)
            throw new RuntimeException("Friendship request is not pending!");

        Friendship friendship = new Friendship(new Tuple<>(fromId, toId));
        if (friendshipRepository.save(friendship).isPresent())
            throw new EntityAlreadyExistsException(friendship);

        friendshipRequest.setStatus(FriendshipRequestStatus.ACCEPTED);
        friendshipRequestRepository.update(friendshipRequest);

        notifyObservers();
    }

    public void  rejectFriendRequest(Long fromId, Long toId) {
        User from = userRepository.findOne(fromId)
                .orElseThrow(() -> new EntityDoesNotExistException(fromId));
        User to = userRepository.findOne(toId)
                .orElseThrow(() -> new EntityDoesNotExistException(toId));

        FriendshipRequest friendshipRequest = friendshipRequestRepository.findOne(new Tuple<>(fromId, toId))
                .orElseThrow(() -> new EntityDoesNotExistException(new FriendshipRequest(new Tuple<>(fromId, toId), FriendshipRequestStatus.PENDING)));

        if (friendshipRequest.getStatus() != FriendshipRequestStatus.PENDING)
            throw new RuntimeException("Friendship request is not pending!");

        friendshipRequest.setStatus(FriendshipRequestStatus.REJECTED);
        friendshipRequestRepository.update(friendshipRequest);

        notifyObservers();
    }

    public List<User> getPendingFriendRequestsOfUser(Long id) {
        userRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        List<User> friends = new ArrayList<>();
        friendshipRequestRepository.findAll().forEach(friendshipRequest -> {
            if (Objects.equals(friendshipRequest.getId().getRight(), id)
                    && friendshipRequest.getStatus() == FriendshipRequestStatus.PENDING) {
                friends.add(userRepository.findOne(friendshipRequest.getId().getLeft())
                        .orElseThrow(() -> new EntityDoesNotExistException(friendshipRequest.getId().getLeft())));
            }

        });
        return friends;
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
