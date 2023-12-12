package com.example.domain;

import java.time.LocalDateTime;

public class Message extends Entity<Long> {

    private Long fromId;

    private String message;

    private LocalDateTime date;

    private Long replyId;

    public Message(Long aLong, Long fromId, String message, LocalDateTime date, Long replyId) {
        super(aLong);
        this.fromId = fromId;
        this.message = message;
        this.date = date;
        this.replyId = replyId;
    }

    public Message(Long fromId, String message, LocalDateTime date, Long replyId) {
        this.fromId = fromId;
        this.message = message;
        this.date = date;
        this.replyId = replyId;
    }

    public Long getFromId() {
        return fromId;
    }

    public void setFromId(Long fromId) {
        this.fromId = fromId;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public Long getReplyId() {
        return replyId;
    }

    public void setReplyId(Long replyId) {
        this.replyId = replyId;
    }
}
