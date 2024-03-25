package org.example.demo;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.repository.*;
import org.example.service.*;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

public class FestivalApplication extends Application {

    private UserService userService;

    private TicketService ticketService;

    private ConcertService concertService;

    @Override
    public void start(Stage stage) throws IOException {
        Properties properties = new Properties();

        try {
            FileInputStream input = new FileInputStream("src/main/resources/db.properties");
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

        userService = new UserServiceImpl(userRepository);
        concertService = new ConcertServiceImpl(concertRepository);
        ticketService = new TicketServiceImpl(userRepository, concertRepository, ticketRepository);

        initView(stage);
        stage.show();
    }

    private void initView(Stage primaryStage) throws IOException {

        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("log-in-sign-up-view.fxml"));
        AnchorPane layout = loader.load();
        primaryStage.setScene(new Scene(layout));

        LogInSignUpController logInSignUpController = loader.getController();
        logInSignUpController.setService(userService, ticketService, concertService);
    }

    public static void main(String[] args) {
        launch();
    }
}