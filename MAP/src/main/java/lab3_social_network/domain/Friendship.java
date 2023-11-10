package lab3_social_network.domain;

import java.time.LocalDateTime;


public class Friendship extends Entity<Tuple<Long,Long>> {

    LocalDateTime createdDate;

    public Friendship(Tuple<Long, Long> id) {
        super(id);
        this.createdDate = LocalDateTime.now();
    }

    public Friendship(User user1, User user2) {
        super(new Tuple<>(user1.getId(), user2.getId()));
        this.createdDate = LocalDateTime.now();
    }

    public Friendship(Tuple<Long, Long> id, LocalDateTime createdDate) {
        super(id);
        this.createdDate = createdDate;
    }

    /**
     *
     * @return the date when the friendship was created
     */
    public LocalDateTime getCreatedDate() {
        return createdDate;
    }

    @Override
    public String toString() {
        return "Friendship{" +
                "id=" + id +
                ", createdDate=" + createdDate +
                '}';
    }
}