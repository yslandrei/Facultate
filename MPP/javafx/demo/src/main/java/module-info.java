module org.example.demo {
    requires javafx.controls;
    requires javafx.fxml;

    requires java.sql;
    requires org.slf4j;

    opens org.example.domain to javafx.base;
    exports org.example.domain;

    opens org.example.demo to javafx.fxml;
    exports org.example.demo;

}