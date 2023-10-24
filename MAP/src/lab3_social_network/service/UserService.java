package lab3_social_network.service;

import lab3_social_network.domain.Friendship;
import lab3_social_network.domain.Tuple;
import lab3_social_network.domain.User;
import lab3_social_network.domain.exceptions.EntityAlreadyExistsException;
import lab3_social_network.domain.exceptions.EntityDoesNotExistException;
import lab3_social_network.domain.graph.BidirectedGraph;
import lab3_social_network.domain.graph.GraphAlgorithmsExecuter;
import lab3_social_network.repository.FriendshipFileRepository;
import lab3_social_network.repository.UserFileRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class UserService {

    private final UserFileRepository userFileRepository;

    private final FriendshipFileRepository friendshipFileRepository;

    private final BidirectedGraph<User> communityGraph;

    private final GraphAlgorithmsExecuter<User> graphAlgorithmsExecuter;

    public UserService(UserFileRepository userFileRepository, FriendshipFileRepository friendshipFileRepository) {
        this.userFileRepository = userFileRepository;
        this.friendshipFileRepository = friendshipFileRepository;
        this.communityGraph = new BidirectedGraph<>();
        this.graphAlgorithmsExecuter = new GraphAlgorithmsExecuter<>(communityGraph);
        userFileRepository.findAll().forEach(communityGraph::addVertex);
        friendshipFileRepository.findAll().forEach(friendship -> {
            User user1 = userFileRepository.findOne(friendship.getId().getLeft());
            User user2 = userFileRepository.findOne(friendship.getId().getRight());
            communityGraph.addEdge(user1, user2);
        });
    }

    public void addUser(User user) {
        if (userFileRepository.save(user) != null)
            throw new EntityAlreadyExistsException(user);

        communityGraph.addVertex(user);
    }

    public void removeUser(Long id) {
        User deletedUser = userFileRepository.delete(id);
        if (deletedUser == null)
            throw new EntityDoesNotExistException(id);

        communityGraph.removeVertex(deletedUser);
        friendshipFileRepository.findAll().forEach(friendship -> {
            if (Objects.equals(friendship.getId().getLeft(), id)) {
                friendshipFileRepository.delete(new Tuple<>(friendship.getId().getLeft(), id));
            }
            else if (Objects.equals(friendship.getId().getRight(), id)) {
                friendshipFileRepository.delete(new Tuple<>(id, friendship.getId().getRight()));
            }
        });
    }

    public void updateUser(User user) {
        if (userFileRepository.update(user) != null)
            throw new EntityDoesNotExistException(user.getId());
    }

    public List<User> getAllUsers() {
        List<User> users = new ArrayList<>();
        userFileRepository.findAll().forEach(users::add);
        return users;
    }

    public User extractUser(List<String> args) {
        return userFileRepository.extractEntity(args);
    }

    public void addFriendToUser(Long userId, Long friendId) {
        User user = userFileRepository.findOne(userId);
        if (user == null)
            throw new EntityDoesNotExistException(userId);
        User friend = userFileRepository.findOne(friendId);
        if (friend == null)
            throw new EntityDoesNotExistException(friendId);

        communityGraph.addEdge(user, friend);
        Friendship newFriendship = new Friendship(new Tuple<>(userId, friendId));
        if (friendshipFileRepository.save(newFriendship) != null)
            throw new EntityAlreadyExistsException(newFriendship);
    }

    public void removeFriendFromUser(Long userId, Long friendId) {
        User user = userFileRepository.findOne(userId);
        if (user == null)
            throw new EntityDoesNotExistException(userId);
        User friend = userFileRepository.findOne(friendId);
        if (friend == null)
            throw new EntityDoesNotExistException(friendId);

        communityGraph.removeEdge(user, friend);
        if (friendshipFileRepository.delete(new Tuple<>(userId, friendId)) == null &&
                friendshipFileRepository.delete(new Tuple<>(friendId, userId)) == null) {
            throw new EntityDoesNotExistException(new Friendship(new Tuple<>(userId, friendId)));
        }
    }

    public List<User> getFriendsOfUser(User user) {
        if (userFileRepository.findOne(user.getId()) == null)
            throw new EntityDoesNotExistException(user);

        List<User> friends = new ArrayList<>();
        friendshipFileRepository.findAll().forEach(friendship -> {
            if (Objects.equals(friendship.getId().getLeft(), user.getId())) {
                friends.add(userFileRepository.findOne(friendship.getId().getRight()));
            }
            else if (Objects.equals(friendship.getId().getRight(), user.getId())) {
                friends.add(userFileRepository.findOne(friendship.getId().getLeft()));
            }
        });
        return friends;
    }

    public Integer getNumberOfCommunities() {
        graphAlgorithmsExecuter.computeComponents();
        return graphAlgorithmsExecuter.getComponentsSize();
    }

    public List<User> getLargestCommunity() {
        graphAlgorithmsExecuter.computeComponents();
        List<User> largestCommunity = new ArrayList<>();
        graphAlgorithmsExecuter.getAllComponents().forEach(component -> {
            if (component.size() > largestCommunity.size()) {
                largestCommunity.clear();
                largestCommunity.addAll(component);
            }
        });
        return largestCommunity;
    }

}
