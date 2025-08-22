package jogo;

public class Map {
    private final int tam;
    private final String[][] coord;

    public Map(int tam) {
        this.tam = tam;
        this.coord = new String[tam][tam];
        limpar();
    }

    public int getTam() { return tam; }

    public void limpar() {
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                coord[i][j] = ".";
            }
        }
    }

    // Marca dois personagens no grid
    public void plot(int x1, int y1, String c1, int x2, int y2, String c2) {
        limpar();
        coord[y1][x1] = c1; // linha = y, coluna = x
        coord[y2][x2] = c2;
    }

    public String render() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                sb.append(coord[i][j]);
                if (j < tam - 1) sb.append(' ');
            }
            if (i < tam - 1) sb.append('\n');
        }
        return sb.toString();
    }
}
