namespace WindowsFormsApp1.utils;

public interface IObservable
{
    void AddObserver(IObserver observer);

    void RemoveObserver(IObserver observer);

    void NotifyObservers();
}