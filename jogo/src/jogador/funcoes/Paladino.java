package jogador.funcoes;

import jogador.Personagem;

public class Paladino extends Personagem {
    public Paladino(int posX, int posY) {
        super("Paladino", posX, posY, 14.0); // super(): vida base 14
        setDano(4.0);
        setDefesa(0.30);
        setAlcance(2);
        setDescricao(
            "O paladino é a chama viva da justiça; entre aço e oração, ergue-se como guardião dos inocentes."
        );
    }
}
