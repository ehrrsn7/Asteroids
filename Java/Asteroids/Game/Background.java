
package Asteroids.Game;

import java.awt.Color;

import javax.swing.JPanel;

public class Background extends JPanel {

    private static final long serialVersionUID = 1L;
    public static Color backgroundColor = Color.BLACK;

    public Background() {
        setOpaque(true);
        setBackground(backgroundColor);
    }
}
