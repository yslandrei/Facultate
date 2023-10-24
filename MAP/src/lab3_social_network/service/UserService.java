package lab3_social_network.service;

import lab3_social_network.domain.Friendship;
import lab3_social_network.domain.Tuple;
import lab3_social_network.domain.User;
import lab3_social_network.domain.exceptions.EntityAlreadyExistsException;
import lab3_social_network.domain.exceptions.EntityDoesNotExistException;
import lab3_social_network.repository.EntityFileRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class UserService {

    private final EntityFileRepository<Long, User> userFileRepository;

    private final EntityFileRepository<Tuple<Long, Long>, Friendship> friendshipFileRepository;

    public UserService(EntityFileRepository<Long, User> userFileRepository, EntityFileRepository<Tuple<Long, Long>, Friendship> friendshipFileRepository) {
        this.userFileRepository = userFileRepository;
        this.friendshipFileRepository = friendshipFileRepository;
    }

    public void addUser(User user) {
        if (userFileRepository.save(user) != null)
            throw new EntityAlreadyExistsException(user);
    }

    public void removeUser(Long id) {
        if (userFileRepository.delete(id) == null)
            throw new EntityDoesNotExistException(id);

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

    public void addFriendToUser(User user, User friend) {
        if (userFileRepository.findOne(user.getId()) == null)
            throw new EntityDoesNotExistException(user);
        if (userFileRepository.findOne(friend.getId()) == null)
            throw new EntityDoesNotExistException(friend);

        Friendship newFriendship = new Friendship(new Tuple<>(user.getId(), friend.getId()));
        if (friendshipFileRepository.save(newFriendship) != null)
            throw new EntityAlreadyExistsException(newFriendship);
    }

    public void removeFriendFromUser(User user, User friend) {
        if (userFileRepository.findOne(user.getId()) == null)
            throw new EntityDoesNotExistException(user);
        if (userFileRepository.findOne(friend.getId()) == null)
            throw new EntityDoesNotExistException(friend);

        if (friendshipFileRepository.delete(new Tuple<>(user.getId(), friend.getId())) == null &&
            friendshipFileRepository.delete(new Tuple<>(friend.getId(), user.getId())) == null) {
            throw new EntityDoesNotExistException(new Friendship(new Tuple<>(user.getId(), friend.getId())));
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

}
