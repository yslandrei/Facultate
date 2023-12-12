package com.example.domain;

public class MessageReceiver extends Entity<Long>{

    private Long toId;

    private Long messageId;

    public MessageReceiver(Long id, Long toId, Long messageId) {
        super(id);
        this.toId = toId;
        this.messageId = messageId;
    }

    public MessageReceiver(Long toId, Long messageId) {
        this.toId = toId;
        this.messageId = messageId;
    }

    public Long getToId() {
        return toId;
    }

    public void setToId(Long toId) {
        this.toId = toId;
    }

    public Long getMessageId() {
        return messageId;
    }

    public void setMessageId(Long messageId) {
        this.messageId = messageId;
    }
}
