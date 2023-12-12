package com.example.map_javafx;

import com.example.domain.*;
import com.example.repository.database.MessageDatabaseRepository;
import com.example.service.FriendshipRequestService;
import com.example.service.FriendshipService;
import com.example.service.MessageService;
import com.example.service.UserService;
import com.example.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class UserController implements Observer {

    private ObservableList<String> observableListFriends = FXCollections.observableArrayList();

    private List<User> listFriends = new ArrayList<>();

    private ObservableList<String> observableListFriendRequests = FXCollections.observableArrayList();

    private List<User> listFriendRequests = new ArrayList<>();

    private ObservableList<String> observableListMessages = FXCollections.observableArrayList();

    private List<Message> listMessages = new ArrayList<>();

    @FXML
    private ListView<String> listViewFriends;
    @FXML
    private ListView<String> listViewFriendRequests;
    @FXML
    private Label labelUsername;
    @FXML
    private TextField textFieldSendFriendRequest;
    @FXML
    private Button buttonSendFriendRequest;
    @FXML
    private Button buttonChat;
    @FXML
    private Button buttonRejectFriendRequest;
    @FXML
    private Button buttonAcceptFriendRequest;
    @FXML
    private Button buttonSendMessage;
    @FXML
    private Button buttonReplyMessage;
    @FXML
    private TextArea textAreaWriteMessage;
    @FXML
    private ListView<String> listViewMessages;

    private User loggedUser;

    private List<User> chattingUsers = new ArrayList<>();

    private Message selectedMessage = null;

    private UserService userService;

    private FriendshipService friendshipService;

    private FriendshipRequestService friendshipRequestService;

    private MessageService messageService;

    public void setService(User loggedUser, UserService userService, FriendshipService friendshipService, FriendshipRequestService friendshipRequestService, MessageService messageService) {
        this.loggedUser = loggedUser;
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.friendshipRequestService = friendshipRequestService;
        this.messageService = messageService;
        this.userService.addObserver(this);
        this.friendshipService.addObserver(this);
        this.friendshipRequestService.addObserver(this);
        this.messageService.addObserver(this);
        initFriendsList();
        initFriendRequestsList();
        labelUsername.setText(loggedUser.getUsername());
    }

    @FXML
    public void initialize() {
        listViewFriends.setItems(observableListFriends);
        listViewFriends.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        listViewFriendRequests.setItems(observableListFriendRequests);
        listViewMessages.setItems(observableListMessages);
    }

    private void initFriendsList() {
        listFriends = friendshipService.getFriendsOfUser(loggedUser.getId());
        observableListFriends.setAll(listFriends.stream()
                .map(User::getUsername).toList());
        if (observableListFriends.isEmpty())
            observableListFriends.add("");
    }

    private void initFriendRequestsList() {
        listFriendRequests = friendshipRequestService.getPendingFriendRequestsOfUser(loggedUser.getId());
        observableListFriendRequests.setAll(listFriendRequests.stream()
                .map(User::getUsername).toList());
        if (observableListFriendRequests.isEmpty())
            observableListFriendRequests.add("");
    }

    private void initMessagesList() {
        if (chattingUsers.size() != 1) {
            listMessages.clear();
            observableListMessages.setAll();
            return;
        }

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        listMessages = messageService.getMessagesBetweenTwoUsers(loggedUser.getId(), chattingUsers.get(0).getId());
        observableListMessages.setAll(listMessages.stream()
                .map(message -> {
                    String replyText = "";
                    if (message.getReplyId() != null) {
                        Message replyMessage = messageService.getMessageById(message.getReplyId());
                        replyText = "Replying to: "
                                + (replyMessage.getFromId().equals(loggedUser.getId()) ? "You: " + replyMessage.getMessage()
                                    : userService.getUserById(replyMessage.getFromId()).getUsername() + ": " + replyMessage.getMessage())
                                + "\n";
                    }
                    return replyText + (message.getFromId().equals(loggedUser.getId()) ? message.getDate().format(formatter) + " | You: " + message.getMessage()
                        : message.getDate().format(formatter) + " | " + chattingUsers.get(0).getUsername() + ": " + message.getMessage());
                }).toList());
        if (observableListMessages.isEmpty())
            observableListMessages.add("");
    }

    public void handleSendFriendRequest() {
        try {
            User friend = userService.getUserByUsername(textFieldSendFriendRequest.getText());
            friendshipRequestService.sendFriendRequest(loggedUser.getId(), friend.getId());
            textFieldSendFriendRequest.setText("");
        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    public void handleAcceptFriendRequest() {
        if (listViewFriendRequests.getSelectionModel().getSelectedIndex() == -1)
            return;
        User from = listFriendRequests.get(listViewFriendRequests.getSelectionModel().getSelectedIndex());
        try {
            friendshipRequestService.acceptFriendRequest(from.getId(), loggedUser.getId());
        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    public void handleRejectFriendRequest() {
        if (listViewFriendRequests.getSelectionModel().getSelectedIndex() == -1)
            return;
        User from = listFriendRequests.get(listViewFriendRequests.getSelectionModel().getSelectedIndex());
        try {
            friendshipRequestService.rejectFriendRequest(from.getId(), loggedUser.getId());
        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    public void handleChat() {
        if (listViewFriends.getSelectionModel().getSelectedIndices().isEmpty())
            return;
        selectedMessage = null;
        buttonReplyMessage.setText("Reply");
        chattingUsers = listViewFriends.getSelectionModel().getSelectedIndices()
                .stream().map(listFriends::get).toList();
        initMessagesList();
    }

    public void handleSendMessage() {
        String message = textAreaWriteMessage.getText();
        try {
            messageService.sendMessage(loggedUser.getId(), chattingUsers.stream().map(Entity::getId).toList(), message, selectedMessage == null ? null : selectedMessage.getId());
            textAreaWriteMessage.setText("");
            selectedMessage = null;
            buttonReplyMessage.setText("Reply");
        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    public void handleReplyMessage() {
        if (selectedMessage != null) {
            selectedMessage = null;
            buttonReplyMessage.setText("Reply");
            return;
        }
        if (listViewMessages.getSelectionModel().getSelectedIndex() == -1)
            return;

        selectedMessage = listMessages.get(listViewMessages.getSelectionModel().getSelectedIndex());
        buttonReplyMessage.setText("CancelReply");
    }

    @Override
    public void update() {
        initFriendsList();
        initFriendRequestsList();
        initMessagesList();
    }

}