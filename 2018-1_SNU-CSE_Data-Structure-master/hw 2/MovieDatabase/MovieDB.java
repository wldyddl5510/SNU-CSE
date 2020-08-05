import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Genre, Title 을 관리하는 영화 데이터베이스.
 *
 * MyLinkedList를 사용해 각각 Genre와 Title에 따라 내부적으로 정렬된 상태를
 * 유지하는 데이터베이스이다.
 */
public class MovieDB { //linked list with node = genre & number of genre
    private Genre head;
    private int numGenre;

    public void setNumGenre(int i) {
        this.numGenre = i;
    }

    public int getNumGenre() { //howmany numbers of genre
        return this.numGenre;
    }

    public MovieDB() { // create new linked list with head node is null and number of genre is 0
        head = new Genre(null);
        head.setGenre_Movie(null);
        this.setNumGenre(0);
    }
    //@Override
    public boolean isEmpty() { //check whether list is empty
        if(this.getNumGenre() == 0)
            return true;
        else
            return false;
    }

    public void insertNewGenre(Genre current_Genre_before, MovieDBItem item) {
        Genre newGenre = new Genre(item.getGenre()); //include new genre
        MovieList newMovie = new MovieList(); //include new movielist in this genre
        newMovie.add(item.getTitle());
        newGenre.setGenre_Movie(newMovie); //made full new genre set
        if(current_Genre_before.getNext() != null) // if not last genre
            newGenre.setNext(current_Genre_before.getNext()); // next should be assigned if next is not null
        current_Genre_before.setNext(newGenre);
        this.setNumGenre(this.getNumGenre() + 1);
    }

    public void insert(MovieDBItem item) {
        Genre current_Genre = this.head;

        while(true) { //order by lexicographical order
            if(this.isEmpty() == true) { // if empty list, create new node and insert next to head
                this.insertNewGenre(current_Genre, item);
                return;
            }
            else { //not empty
                if(current_Genre.getNext() == null) { //boundary condition(first or last)
                    this.insertNewGenre(current_Genre, item);
                    return;
                }
                int indicator = current_Genre.getNextItem().compareTo(item.getGenre()); //indicator to check lexicographical order
                if(indicator == 0) { // already existing genre
                    current_Genre.getNextGenreMovie().add(item.getTitle()); //add to existing genre
                    return;
                }
                else if(indicator > 0) { //between current and getNext
                    this.insertNewGenre(current_Genre, item);
                    return;
                }
                else {
                    current_Genre = current_Genre.getNext(); // move to next
                }
            }
        }
    }

    public void removeGenre(Genre prevDelete) { //remove next entire genre
        prevDelete.getNext().getGenreMovie().removeAll();
        prevDelete.setNext(prevDelete.getNext().getNext());
        this.setNumGenre(this.getNumGenre() - 1);
    }

    public void delete(MovieDBItem item) {
        Genre current_Genre = this.head;
        if(isEmpty() == true) //no deletion
            return;
        while(true) {
            if(current_Genre.getNext() == null) //nothing to delete
                return;
            int indicator = current_Genre.getNextItem().compareTo(item.getGenre()); //to find the item
            if(indicator == 0) { // existing genre
                if(current_Genre.getNextGenreMovie().size() == 1) { //only one element
                    if(current_Genre.getNextGenreMovie().first().compareTo(item.getTitle()) == 0) //if deletion is exactly that movie
                        this.removeGenre(current_Genre); //delete genre entriely
                    return; //end loop
                }
                current_Genre.getNextGenreMovie().delete(item.getTitle()); //delete Movie in that Genre
                return;
            }
            else {
                current_Genre = current_Genre.getNext();
            }
        }
    }

    public MyLinkedList<MovieDBItem> search(String term) {
        Genre currentGenre = this.head;
        MyLinkedList<MovieDBItem> SearchRes = new MyLinkedList<>(); //save results
        if(isEmpty() == true) { //noting to search
            return SearchRes;
        }
        for(int i = 0 ; i < numGenre ; i++) { //find proper genre
            currentGenre = currentGenre.getNext();
            MovieList GenreMovieList = currentGenre.getGenreMovie();

            MovieListIterator it = new MovieListIterator(GenreMovieList);
            while(it.hasNext()) {
                String MovieName = it.next(); //get name
                if(MovieName.contains(term)) { //if proper result
                    MovieDBItem ProperMovie = new MovieDBItem(currentGenre.getGenreName(), MovieName);
                    SearchRes.add(ProperMovie);
                }
            }
        }
        return SearchRes;
    }

    public MyLinkedList<MovieDBItem> items() {
        //convert MovieDB to MyLinkedList<MovieDbItem>

        MyLinkedList<MovieDBItem> res = new MyLinkedList<>();
        if(this.getNumGenre() == 0) { //null list for empty MovieDB
            return res;
        }
        else {
            Genre current = this.head.getNext();
            while(true) {
                Node<String> Moviecurrent = current.getGenreMovie().getNode(1);
                while(true) { //move one genre
                    MovieDBItem addedMovie = new MovieDBItem(current.getGenreName(), Moviecurrent.getItem());
                    res.add(addedMovie);
                    if(Moviecurrent.getNext() != null)
                        Moviecurrent = Moviecurrent.getNext();
                    else //if no next exists
                        break;
                }
                if(current.getNext() != null) //go to next genre
                    current = current.getNext();
                else //if ends
                    break;
            }
        }
        return res;
    }
}

class Genre extends Node<String> implements Comparable<Genre> {
    private MovieList Genre_Movie; //name of genre + movie list for each genre

    public Genre(String name) {
        super(name); // new node : item = name & next = null
        this.Genre_Movie = new MovieList();
    }

    @Override
    public Genre getNext() {
        return (Genre)super.getNext();
    }

    public String getGenreName() {
        return this.getItem();
    }

    public MovieList getGenreMovie() {
        return Genre_Movie;
    }

    public MovieList getNextGenreMovie() {
        return this.getNext().getGenreMovie();
    }

    public String getNextItem() {
        return this.getNext().getItem();
    }

    public void setGenre_Movie(MovieList m) {
        this.Genre_Movie = m;
    }

    @Override
    public int compareTo(Genre o) {
        return this.getItem().compareTo(o.getItem());
    }

    @Override
    public int hashCode() {
        throw new UnsupportedOperationException("not implemented yet");
    }

    @Override
    public boolean equals(Object obj) {
        throw new UnsupportedOperationException("not implemented yet");
    }
}

class MovieList implements ListInterface<String> { //linked list with movies for same Genre
    private Node<String> head;
    private int numItems;

    public void setSize(int i) {
        this.numItems = i;
    }

    public MovieList() {
        this.head = new Node<>(null);
        this.setSize(0);
    }

    @Override
    public Iterator<String> iterator() {
        return new MovieListIterator(this);
    }

    @Override
    public boolean isEmpty() {
        if (this.size() == 0)
            return true;
        else
            return false;
    }

    @Override
    public int size() {
        return this.numItems;
    }

    @Override
    public void add(String item) {
        Node<String> newItem = new Node<>(item); // new node having the name
        if (this.isEmpty() == true) { //empty : next to head
            this.head.setNext(newItem);
        }
        else {
            Node<String> current = this.head;
            while (true) {
                if (current.getNext() == null) { //if no next exists
                    current.setNext(newItem); // add to last
                    break;
                }
                else if ((current.getNext().getItem().compareTo(item) > 0)) { // item is in current~cur.next
                    newItem.setNext(current.getNext()); // (InsertItem->b)
                    current.setNext(newItem); //(a->insertItem)->b
                    break;
                }
                else if ((current.getNext().getItem().compareTo(item) == 0)) { //if same input comes
                    return; //ends with no action
                }
                else {
                    current = current.getNext();
                }
            }
        }
        this.setSize(this.size() + 1);// count + 1
    }

    public void delete(String item) {
        Node<String> current = this.head;
        while (true) {
            if (current.getNext() == null) //no proper deletion
                return; //ends with no action
            if (current.getNext().getItem().compareTo(item) == 0) {  //cur -> cur.next(delete)
                current.setNext(current.getNext().getNext()); //cur -> cur.next.next
                this.setSize(this.size() - 1);
                return;
            }
            else {
                current = current.getNext();
            }
        }
    }

    public Node<String> getNode(int i) { //0 is head, n is last node
        if (i > this.size()) {
            return null;
        } else {
            Node<String> current = this.head;
            while (i > 0) {
                current = current.getNext();
                i--;
            }
            return current;
        }
    }

    @Override
    public String first() {
        return this.head.getNext().getItem();
    }

    @Override
    public void removeAll() {
        this.head.setNext(null);
        this.setSize(0);
    }
}

class MovieListIterator implements Iterator<String> {
    private MovieList list;
    private Node<String> current;
    private Node<String> previous;

    public MovieListIterator(MovieList list) {
        this.list = list;
        this.current = list.getNode(0); //head
        this.previous = null;
    }

    @Override
    public boolean hasNext() {
        return current.getNext() != null;
    }

    @Override
    public String next() {
        if(!hasNext())
            throw new NoSuchElementException();
        previous = current;
        current = current.getNext();

        return current.getItem();
    }

    @Override
    public void remove() {
        if (previous == null)
            throw new IllegalStateException("next() should be called first");
        if (current == null)
            throw new NoSuchElementException();
        previous.removeNext();
        list.setSize(list.size() - 1);
        current = previous;
        previous = null;
    }
}