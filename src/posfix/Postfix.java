import java.io.*;

public class Postfix {
   public static void main(String[] args) throws IOException {
      Parser parse = new Parser();
      parse.expr();
      System.out.write('\n'); 
   }
}

