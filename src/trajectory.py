import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../trajectory.csv")

def moon():
    plt.figure(figsize=(8, 8))
    plt.plot(df["moon_x"], df["moon_y"], color="gray")
    plt.xlabel("x [m]")
    plt.ylabel("y [m]")
    plt.title("Moon-trajectory around the sun")
    plt.axis("equal")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

def scaled():
    scale = 20

    df["moon_vis_x"] = df["earth_x"] + (df["moon_x"] - df["earth_x"]) * scale
    df["moon_vis_y"] = df["earth_y"] + (df["moon_y"] - df["earth_y"]) * scale

    plt.figure(figsize=(10, 10))
    plt.plot(df["earth_x"], df["earth_y"], label="Earth", color="blue")
    plt.plot(df["moon_vis_x"], df["moon_vis_y"], label=f"Moon (x{scale})", color="purple", alpha=0.8)
    plt.plot(0, 0, 'o', color='orange', label="Sun")

    plt.xlabel("x [m]")
    plt.ylabel("y [m]")
    plt.title(f"Trajectory of the Earth and the Moon around the Sun. Movement of the Moon in relation to Earth scale = (x{scale})")
    plt.axis("equal")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

def main():
    scaled()


if __name__ == "__main__":
    main()