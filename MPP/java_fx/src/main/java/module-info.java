module org.example.javafx {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    requires org.slf4j;
    exports org.example.domain;
    opens org.example.domain to javafx.base;
    opens org.example.java_fx to javafx.fxml;
    exports org.example.java_fx;
}
