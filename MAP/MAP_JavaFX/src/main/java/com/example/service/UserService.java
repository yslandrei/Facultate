package com.example.service;

import com.example.domain.Friendship;
import com.example.domain.Tuple;
import com.example.domain.User;
import com.example.domain.exceptions.EntityAlreadyExistsException;
import com.example.domain.exceptions.EntityDoesNotExistException;
import com.example.domain.graph.BidirectedGraph;
import com.example.domain.graph.GraphAlgorithmsExecuter;
import com.example.repository.file.FriendshipFileRepository;
import com.example.repository.Repository;
import com.example.utils.events.ChangeEventType;
import com.example.utils.events.Event;
import com.example.utils.events.UserChangeEvent;
import com.example.utils.observer.Observable;
import com.example.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class UserService implements Observable<UserChangeEvent> {

    private final Repository<Long, User> userRepository;

    private final Repository<Tuple<Long, Long>, Friendship> friendshipFileRepository;

    private final BidirectedGraph<User> communityGraph;

    private final GraphAlgorithmsExecuter<User> graphAlgorithmsExecuter;

    private List<Observer<UserChangeEvent>> observers = new ArrayList<>();

    public UserService(Repository<Long, User> userRepository, Repository<Tuple<Long, Long>, Friendship> friendshipFileRepository) {
        this.userRepository = userRepository;
        this.friendshipFileRepository = friendshipFileRepository;
        this.communityGraph = new BidirectedGraph<>();
        this.graphAlgorithmsExecuter = new GraphAlgorithmsExecuter<>(communityGraph);

        userRepository.findAll().forEach(communityGraph::addVertex);
        friendshipFileRepository.findAll().forEach(friendship -> {
            User user1 = userRepository.findOne(friendship.getId().getLeft())
                    .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getLeft()));
            User user2 = userRepository.findOne(friendship.getId().getRight())
                    .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getRight()));
            communityGraph.addEdge(user1, user2);
        });
    }

    public void addUser(User user) {
        if (userRepository.save(user).isPresent())
            throw new EntityAlreadyExistsException(user);

        communityGraph.addVertex(user);

        notifyObservers(new UserChangeEvent(ChangeEventType.ADD, user));
    }

    public void removeUser(Long id) {
        User deletedUser = userRepository.delete(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        friendshipFileRepository.findAll().forEach(friendship -> {
            if (Objects.equals(friendship.getId().getLeft(), id)) {
                friendshipFileRepository.delete(friendship.getId());
            }
            else if (Objects.equals(friendship.getId().getRight(), id)) {
                friendshipFileRepository.delete(friendship.getId());
            }
        });

        communityGraph.removeVertex(deletedUser);

        notifyObservers(new UserChangeEvent(ChangeEventType.DELETE, deletedUser));
    }

    public void updateUser(User user) {
        if (userRepository.update(user).isPresent())
            throw new EntityDoesNotExistException(user.getId());

        notifyObservers(new UserChangeEvent(ChangeEventType.UPDATE, user));
    }

    public List<User> getAllUsers() {
        List<User> users = new ArrayList<>();
        userRepository.findAll().forEach(users::add);
        return users;
    }

    public void addFriendToUser(Long userId, Long friendId) {
        User user = userRepository.findOne(userId)
                .orElseThrow(() -> new EntityDoesNotExistException(userId));
        User friend = userRepository.findOne(friendId)
                .orElseThrow(() -> new EntityDoesNotExistException(friendId));

        Friendship newFriendship = new Friendship(new Tuple<>(userId, friendId));
        if (friendshipFileRepository.save(newFriendship).isPresent())
            throw new EntityAlreadyExistsException(newFriendship);

        communityGraph.addEdge(user, friend);
    }

    public void removeFriendFromUser(Long userId, Long friendId) {
        User user = userRepository.findOne(userId)
                .orElseThrow(() -> new EntityDoesNotExistException(userId));
        User friend = userRepository.findOne(friendId)
                .orElseThrow(() -> new EntityDoesNotExistException(friendId));

        if (friendshipFileRepository.delete(new Tuple<>(userId, friendId)).isEmpty() &&
                friendshipFileRepository.delete(new Tuple<>(friendId, userId)).isEmpty()) {
            throw new EntityDoesNotExistException(new Friendship(new Tuple<>(userId, friendId)));
        }

        communityGraph.removeEdge(user, friend);
    }

    public List<User> getFriendsOfUser(Long id) {
        userRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        List<User> friends = new ArrayList<>();
        friendshipFileRepository.findAll().forEach(friendship -> {
            if (Objects.equals(friendship.getId().getLeft(), id)) {
                friends.add(userRepository.findOne(friendship.getId().getRight())
                        .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getRight())));
            }
            else if (Objects.equals(friendship.getId().getRight(), id)) {
                friends.add(userRepository.findOne(friendship.getId().getLeft())
                        .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getLeft())));
            }
        });
        return friends;
    }

    public List<User> getFriendsOfUserFromMonth(Long id, Integer month) {
        userRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        List<User> friends = new ArrayList<>();
        friendshipFileRepository.findAll().forEach(friendship -> {
            if (Objects.equals(friendship.getId().getLeft(), id)
                    && friendship.getCreatedDate().getMonth().getValue() == month) {
                friends.add(userRepository.findOne(friendship.getId().getRight())
                        .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getRight())));
            }
            else if (Objects.equals(friendship.getId().getRight(), id)
                    && friendship.getCreatedDate().getMonth().getValue() == month) {
                friends.add(userRepository.findOne(friendship.getId().getLeft())
                        .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getLeft())));
            }
        });
        return friends;
    }

    public Integer getNumberOfCommunities() {
        graphAlgorithmsExecuter.computeComponents();
        return graphAlgorithmsExecuter.getComponentsSize();
    }

    public Tuple<List<User>, Integer>  getLargestCommunity() {
        graphAlgorithmsExecuter.computeComponents();
        Tuple<List<User>, Integer> largestCommunity = new Tuple<>(new ArrayList<>(), 0);
        graphAlgorithmsExecuter.getAllComponents().forEach(component -> {
            if (component.getRight() > largestCommunity.getRight()) {
                largestCommunity.getLeft().clear();
                largestCommunity.getLeft().addAll(component.getLeft());
                largestCommunity.setRight(component.getRight());
            }
        });
        return largestCommunity;
    }

    @Override
    public void addObserver(Observer<UserChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<UserChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(UserChangeEvent t) {
        observers.forEach(x -> x.update(t));
    }
}
