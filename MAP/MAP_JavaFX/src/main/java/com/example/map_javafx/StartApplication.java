package com.example.map_javafx;

import com.example.domain.Friendship;
import com.example.domain.Tuple;
import com.example.domain.User;
import com.example.domain.validators.FriendshipValidator;
import com.example.domain.validators.UserValidator;
import com.example.repository.Repository;
import com.example.repository.database.FriendshipDatabaseRepository;
import com.example.repository.database.UserDatabaseRepository;
import com.example.service.UserService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class StartApplication extends Application {

    private UserService userService;

    @Override
    public void start(Stage stage) throws IOException {
        Repository<Long, User> userRepository = new UserDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new UserValidator());

        Repository<Tuple<Long, Long>, Friendship>friendshipRepository = new FriendshipDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new FriendshipValidator());
        userService = new UserService(userRepository, friendshipRepository);

        initView(stage);
        stage.setWidth(800);
        stage.show();
    }

    private void initView(Stage primaryStage) throws IOException {

        FXMLLoader userLoader = new FXMLLoader();
        userLoader.setLocation(getClass().getResource("user-view.fxml"));
        AnchorPane userLayout = userLoader.load();
        primaryStage.setScene(new Scene(userLayout));

        UserController userController = userLoader.getController();
        userController.setService(userService);

    }

    public static void main(String[] args) {
        launch();
    }
}