package jogo;

import jogador.Personagem;
import jogador.funcoes.Paladino;
import jogador.funcoes.Samurai;

import java.util.Scanner;

/**
 * Mini-jogo de turnos no console:
 * - Mova o Samurai com W A S D (Enter após digitar a letra).
 * - O Paladino persegue automaticamente.
 * - Se estiverem em alcance, atacam.
 */
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Map mapa = new Map(10);
        Personagem samurai = new Samurai(1, 1);
        Personagem paladino = new Paladino(8, 8);

        System.out.println("=== Samurai vs Paladino ===");
        System.out.println("Controles (Samurai): W A S D + Enter");
        System.out.println("Fim quando alguém cair.\n");

        while (samurai.estaVivo() && paladino.estaVivo()) {
            // Atualiza e mostra o mapa
            mapa.plot(samurai.getX(), samurai.getY(), "S", paladino.getX(), paladino.getY(), "P");
            System.out.println(mapa.render());
            System.out.printf("HP S=%.1f | HP P=%.1f%n", samurai.getVida(), paladino.getVida());
            System.out.print("Movimento do Samurai (W/A/S/D): ");

            String cmd = sc.nextLine().trim().toUpperCase();
            int dx = 0, dy = 0;
            switch (cmd.isEmpty() ? ' ' : cmd.charAt(0)) {
                case 'W': dy = -1; break;
                case 'S': dy = 1;  break;
                case 'A': dx = -1; break;
                case 'D': dx = 1;  break;
                default:
                    System.out.println("Comando inválido. Use W A S D.");
            }
            samurai.mover(dx, dy, mapa.getTam());

            // IA simples do Paladino: aproxima por eixo com maior distância
            int ddx = Integer.compare(samurai.getX(), paladino.getX()); // -1,0,1
            int ddy = Integer.compare(samurai.getY(), paladino.getY());
            // Prioriza o eixo de maior módulo de distância
            int distX = Math.abs(samurai.getX() - paladino.getX());
            int distY = Math.abs(samurai.getY() - paladino.getY());
            if (distX >= distY) paladino.mover(ddx, 0, mapa.getTam());
            else paladino.mover(0, ddy, mapa.getTam());

            // Após movimento, trocam golpes se estiverem em alcance
            if (samurai.distAte(paladino) <= samurai.getAlcance()) {
                samurai.atacar(paladino);
                System.out.println("Samurai ataca!");
            }
            if (paladino.estaVivo() && paladino.distAte(samurai) <= paladino.getAlcance()) {
                paladino.atacar(samurai);
                System.out.println("Paladino ataca!");
            }

            System.out.println();
        }

        // Resultado
        mapa.plot(samurai.getX(), samurai.getY(), "S", paladino.getX(), paladino.getY(), "P");
        System.out.println(mapa.render());
        System.out.printf("HP S=%.1f | HP P=%.1f%n", samurai.getVida(), paladino.getVida());
        if (samurai.estaVivo()) System.out.println(">> Samurai venceu!");
        else if (paladino.estaVivo()) System.out.println(">> Paladino venceu!");
        else System.out.println(">> Ambos caíram!");
    }
}
