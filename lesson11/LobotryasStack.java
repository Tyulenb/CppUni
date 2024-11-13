package lesson11;

import java.util.ArrayDeque;
import java.util.Queue;

public class LobotryasStack <T> {
    Queue<T> q1 = new ArrayDeque<>();
    Queue<T> q2 = new ArrayDeque<>();

    void push(T x){
        while(!q1.isEmpty()){
            q2.add(q1.poll());
        }
        q1.add(x);
        while(!q2.isEmpty()){
            q1.add(q2.poll());
        }
    }

    T top(){
        return q1.peek();
    }

    T pop(){
        return q1.poll();
    }

    boolean empty(){
        return q1.isEmpty();
    }
}
