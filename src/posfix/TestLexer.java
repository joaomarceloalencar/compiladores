import lexer.*;
import java.io.*;
import java.nio.charset.StandardCharsets;

public class TestLexer {
    public static void main(String[] args) throws Exception {
        String[] examples = new String[] {
            "42 + 23\n",
            "x = 5 * (y + 2)\n",
            "true false id123 007\n",
            "sum1 - var2 / 10\n"
        };

        for (int i = 0; i < examples.length; i++) {
            System.out.println("--- Exemplo " + (i+1) + " ---");
            runExample(examples[i]);
            System.out.println();
        }
    }

    private static void runExample(String input) throws Exception {
        // Redireciona System.in para a string de teste
        ByteArrayInputStream in = new ByteArrayInputStream(input.getBytes(StandardCharsets.UTF_8));
        InputStream oldIn = System.in;
        try {
            System.setIn(in);
            Lexer lexer = new Lexer();
            while (true) {
                Token t = lexer.scan();
                // Detecta EOF: quando o lexer cria um Token com tag igual a 0xFFFF
                if (t.tag == 0xFFFF) break;

                if (t instanceof Num) {
                    Num n = (Num) t;
                    System.out.println("NUM(" + n.value + ")");
                } else if (t instanceof Word) {
                    Word w = (Word) t;
                    System.out.println("WORD(tag=" + w.tag + ", lexeme=\"" + w.lexeme + "\")");
                } else {
                    // token simples: imprime o caractere
                    System.out.println("'" + (char) t.tag + "' (tag=" + t.tag + ")");
                }
            }
        } finally {
            System.setIn(oldIn);
        }
    }
}
