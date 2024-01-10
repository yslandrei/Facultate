package com.example.service;

import com.example.domain.Friendship;
import com.example.domain.Tuple;
import com.example.domain.User;
import com.example.domain.exceptions.EntityDoesNotExistException;
import com.example.domain.graph.BidirectedGraph;
import com.example.domain.graph.GraphAlgorithmsExecuter;
import com.example.repository.Repository;
import com.example.repository.database.FriendshipDatabaseRepository;
import com.example.repository.database.UserDatabaseRepository;
import com.example.repository.paging.Page;
import com.example.repository.paging.Pageable;
import com.example.utils.observer.Observable;
import com.example.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class FriendshipService implements Observable {

    private final UserDatabaseRepository userRepository;

    private final FriendshipDatabaseRepository friendshipRepository;

    private List<Observer> observers = new ArrayList<>();

    public FriendshipService(UserDatabaseRepository userRepository, FriendshipDatabaseRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    public List<User> getFriendsOfUser(Long id) {
        userRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        List<User> friends = new ArrayList<>();
        friendshipRepository.findAll().forEach(friendship -> {
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

    public Page<User> getFriendsOfUserPaginated(Long id, Pageable pageable) {
        userRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        return userRepository.executeQueryPaginated("select * from users " +
                        "where id in (select user1_id from friendships where user2_id = %d) ".formatted(id) +
                        "or id in (select user2_id from friendships where user1_id = %d)".formatted(id),
                pageable);
    }

    public List<User> getFriendsOfUserFromMonth(Long id, Integer month) {
        userRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        List<User> friends = new ArrayList<>();
        friendshipRepository.findAll().forEach(friendship -> {
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

    private void storeAndComputeComponents(BidirectedGraph<User> communityGraph, GraphAlgorithmsExecuter<User> graphAlgorithmsExecuter) {
        userRepository.findAll().forEach(communityGraph::addVertex);
        friendshipRepository.findAll().forEach(friendship -> {
            User user1 = userRepository.findOne(friendship.getId().getLeft())
                    .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getLeft()));
            User user2 = userRepository.findOne(friendship.getId().getRight())
                    .orElseThrow(() -> new EntityDoesNotExistException(friendship.getId().getRight()));
            communityGraph.addEdge(user1, user2);
        });
        graphAlgorithmsExecuter.computeComponents();
    }

    public Integer getNumberOfCommunities() {
        BidirectedGraph<User> communityGraph = new BidirectedGraph<>();
        GraphAlgorithmsExecuter<User> graphAlgorithmsExecuter = new GraphAlgorithmsExecuter<>(communityGraph);
        storeAndComputeComponents(communityGraph, graphAlgorithmsExecuter);
        return graphAlgorithmsExecuter.getComponentsSize();
    }

    public Tuple<List<User>, Integer> getLargestCommunity() {
        BidirectedGraph<User> communityGraph = new BidirectedGraph<>();
        GraphAlgorithmsExecuter<User> graphAlgorithmsExecuter = new GraphAlgorithmsExecuter<>(communityGraph);
        storeAndComputeComponents(communityGraph, graphAlgorithmsExecuter);
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
