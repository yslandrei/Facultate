package com.example.domain;

import java.time.LocalDateTime;

public class FriendshipRequest extends Entity<Tuple<Long,Long>> {

    private LocalDateTime createdDate;

    private FriendshipRequestStatus status;

    public FriendshipRequest(Tuple<Long, Long> id, FriendshipRequestStatus status) {
        super(id);
        this.createdDate = LocalDateTime.now();
        this.status = status;
    }

    public FriendshipRequest(Tuple<Long, Long> id, LocalDateTime createdDate, FriendshipRequestStatus status) {
        super(id);
        this.createdDate = createdDate;
        this.status = status;
    }

    public LocalDateTime getCreatedDate() {
        return createdDate;
    }

    public void setCreatedDate(LocalDateTime createdDate) {
        this.createdDate = createdDate;
    }

    public FriendshipRequestStatus getStatus() {
        return status;
    }

    public void setStatus(FriendshipRequestStatus status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "FriendshipRequest{" +
                "id=" + id +
                ", createdDate=" + createdDate +
                ", status=" + status +
                '}';
    }
}
