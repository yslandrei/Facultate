package com.example.map_javafx;

import com.example.domain.*;
import com.example.domain.validators.*;
import com.example.repository.Repository;
import com.example.repository.database.*;
import com.example.repository.paging.Pageable;
import com.example.service.FriendshipRequestService;
import com.example.service.FriendshipService;
import com.example.service.MessageService;
import com.example.service.UserService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class SocialNetworkApplication extends Application {

    private UserService userService;

    private FriendshipService friendshipService;

    private FriendshipRequestService friendshipRequestService;

    private MessageService messageService;

    @Override
    public void start(Stage stage) throws IOException {
        UserDatabaseRepository userDatabaseRepository = new UserDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new UserValidator());

        FriendshipDatabaseRepository friendshipDatabaseRepository = new FriendshipDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new FriendshipValidator());

        FriendshipRequestDatabaseRepository friendshipRequestDatabaseRepository = new FriendshipRequestDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new FriendshipRequestValidator());

        MessageDatabaseRepository messageDatabaseRepository = new MessageDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new MessageValidator());

        MessageReceiverDatabaseRepository messageReceiverDatabaseRepository = new MessageReceiverDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new MessageReceiverValidator());

        userService = new UserService(userDatabaseRepository, friendshipDatabaseRepository);

        friendshipService = new FriendshipService(userDatabaseRepository, friendshipDatabaseRepository);

        friendshipRequestService = new FriendshipRequestService(userDatabaseRepository, friendshipDatabaseRepository, friendshipRequestDatabaseRepository);;

        messageService = new MessageService(userDatabaseRepository, friendshipDatabaseRepository, messageDatabaseRepository, messageReceiverDatabaseRepository);

        initView(stage);
        stage.show();
    }

    private void initView(Stage primaryStage) throws IOException {

        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("log-in-sign-up-view.fxml"));
        AnchorPane layout = loader.load();
        primaryStage.setScene(new Scene(layout));

        LogInSignUpController logInSignUpController = loader.getController();
        logInSignUpController.setService(userService, friendshipService, friendshipRequestService, messageService);
    }

    public static void main(String[] args) {
        launch();
    }
}