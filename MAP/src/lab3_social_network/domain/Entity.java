package lab3_social_network.domain;


import java.io.Serializable;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public abstract class Entity<ID> implements Serializable {

    protected ID id;

    public Entity(ID id) {
        this.id = id;
    }

    public Entity() {

    }

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity<?> entity = (Entity<?>) o;
        return Objects.equals(id, entity.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    public String toString() {
        return id.toString();
    }

    public abstract void fromString(String input);

}