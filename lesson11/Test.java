package lesson11;

import java.util.Stack;

public class Test {
    public static void main(String[] args) {
        LobotryasStack<String> lst = new LobotryasStack<>();
        Stack<String> st = new Stack<>();
        lst.push("a");
        lst.push("b");
        lst.push("c");
        st.push("a");
        st.push("b");
        st.push("c");

        while(!st.empty()){
            System.out.print(st.pop()+" ");
        }
        System.out.println();
        while(!lst.empty()){
            System.out.print(lst.pop()+" ");
        }

        System.out.println();


        lst.push("abc");
        lst.push("defg");

        System.out.println(lst.top());
        System.out.println(lst.pop());
        while(!lst.empty()){
            System.out.print(lst.pop()+" ");
        }
    }
}
