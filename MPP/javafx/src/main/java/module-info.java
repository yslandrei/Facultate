module org.example.javafx {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    requires org.kordamp.bootstrapfx.core;
    requires org.slf4j;
    exports org.example.domain;
    opens org.example.domain to javafx.base;
    opens org.example.javafx to javafx.fxml;
    exports org.example.javafx;
}
