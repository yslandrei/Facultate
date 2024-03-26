package org.example;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.demo.FestivalApplication;
import org.example.demo.LogInSignUpController;
import org.example.repository.*;
import org.example.service.*;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        Properties properties = new Properties();

        try {
            FileInputStream input = new FileInputStream("db.properties");
            try {
                properties.load(input);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        UserRepository userRepository = new UserDatabaseRepositoryImpl(properties);
        ConcertRepository concertRepository = new ConcertDatabaseRepositoryImpl(properties);
        TicketRepository ticketRepository = new TicketDatabaseRepositoryImpl(userRepository, concertRepository, properties);

        UserService userService = new UserServiceImpl(userRepository);
        ConcertService concertService = new ConcertServiceImpl(concertRepository);
        TicketService ticketService = new TicketServiceImpl(userRepository, concertRepository, ticketRepository);

        System.out.println(System.getProperty("user.dir"));
        FXMLLoader loader = new FXMLLoader(getClass().getResource("log-in-sign-up-view.fxml"));
        Parent root = loader.load();
        LogInSignUpController logInSignUpController = loader.getController();
        logInSignUpController.setService(userService, ticketService, concertService);
        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Festival Ticket Store");
        primaryStage.show();
    }
}