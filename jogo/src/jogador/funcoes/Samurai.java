package jogador.funcoes;

import jogador.Personagem;

public class Samurai extends Personagem {
    public Samurai(int posX, int posY) {
        super("Samurai", posX, posY, 12.0); // super(): vida base 12
        setDano(5.0);
        setDefesa(0.10);
        setAlcance(3);
        setDescricao(
            "O samurai é a lâmina da disciplina, moldado pela honra e pelo silêncio. " +
            "Entre aço e vento, sua katana segue o caminho que jurou."
        );
    }
}
