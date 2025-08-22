package jogador;

public abstract class Personagem {
    private String nome;
    private double vida;
    private double dano;
    private double defesa;     // 0.0 a 1.0 (fração reduzida do dano)
    private int alcance;       // distância de ataque (Manhattan)
    private String descricao;
    private int x, y;          // posição no mapa

    protected Personagem(String nome, int x, int y, double vidaBase) {
        this.nome = nome;
        this.x = x;
        this.y = y;
        setVida(vidaBase); // validação via setter
    }

    // --- Regras comuns ---
    public boolean estaVivo() { return vida > 0; }

    public void mover(int dx, int dy, int limite) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < limite && ny >= 0 && ny < limite) {
            x = nx; y = ny;
        }
    }

    // Distância Manhattan (|dx| + |dy|)
    public int distAte(Personagem outro) {
        return Math.abs(this.x - outro.x) + Math.abs(this.y - outro.y);
    }

    public void atacar(Personagem alvo) {
        if (!this.estaVivo() || !alvo.estaVivo()) return;
        if (distAte(alvo) <= this.alcance) {
            double danoBruto = this.dano;
            double danoEfetivo = danoBruto * (1.0 - clamp(alvo.defesa, 0.0, 0.95));
            alvo.receberDano(danoEfetivo);
        }
    }

    private void receberDano(double quantia) {
        setVida(this.vida - Math.max(0, quantia));
    }

    private static double clamp(double v, double a, double b) {
        return Math.max(a, Math.min(b, v));
    }

    // --- Getters/Setters (encapsulamento) ---
    public String getNome() { return nome; }
    public void setNome(String nome) { this.nome = nome != null ? nome : "SemNome"; }

    public double getVida() { return vida; }
    public void setVida(double vida) { this.vida = Math.max(0.0, vida); } // nunca negativa

    public double getDano() { return dano; }
    public void setDano(double dano) { this.dano = Math.max(0.0, dano); }

    public double getDefesa() { return defesa; }
    public void setDefesa(double defesa) { this.defesa = Math.max(0.0, Math.min(0.95, defesa)); }

    public int getAlcance() { return alcance; }
    public void setAlcance(int alcance) { this.alcance = Math.max(0, alcance); }

    public String getDescricao() { return descricao; }
    public void setDescricao(String descricao) { this.descricao = descricao != null ? descricao : ""; }

    public int getX() { return x; }
    public int getY() { return y; }
    public void setPos(int x, int y) { this.x = x; this.y = y; }
}
