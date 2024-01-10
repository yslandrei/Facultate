package com.example.repository.paging;


import java.util.List;

public class Page<E> {

    private List<E> elementsOnPage;

    private int lastPage;

    public Page(List<E> elementsOnPage, int lastPage) {
        this.elementsOnPage = elementsOnPage;
        this.lastPage = lastPage;
    }

    public List<E> getElementsOnPage() {
        return elementsOnPage;
    }

    public int getLastPage() {
        return lastPage;
    }

}

