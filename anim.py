import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

def main():
    scale_factor = 20
    sim_days = 90
    frame_step = 65
    gif_name = "traj_earth_moon_fast.gif"

    df = pd.read_csv("trajectory.csv")

    for col in ["earth_x", "earth_y", "moon_x", "moon_y"]:
        df[col] = pd.to_numeric(df[col], errors="coerce") / 1000.0

    max_time = sim_days * 24 * 3600
    df = df[df["time"] <= max_time].copy()

    earth_x = df["earth_x"].to_numpy()
    earth_y = df["earth_y"].to_numpy()
    moon_x  = df["moon_x"].to_numpy()
    moon_y  = df["moon_y"].to_numpy()

    rel_x = moon_x - earth_x
    rel_y = moon_y - earth_y
    scaled_moon_x = earth_x + scale_factor * rel_x
    scaled_moon_y = earth_y + scale_factor * rel_y

    fig, ax = plt.subplots(figsize=(10, 6))
    ax.set_aspect("equal")
    ax.set_xlim(-5e7, 2e8)
    ax.set_ylim(-5e7, 2e8)
    ax.set_xlabel("x [km]")
    ax.set_ylabel("y [km]")
    ax.set_title(f"Fast-forwarded Earth–Moon trajectory (Moon x{scale_factor})")

    sun_dot,    = ax.plot(0, 0, 'o', color='orange', label='Sun')
    earth_dot,  = ax.plot([], [], 'bo', markersize=5, label='Earth')
    moon_dot,   = ax.plot([], [], 'ro', markersize=4, label=f'Moon (x{scale_factor})')
    earth_line, = ax.plot([], [], 'b-', linewidth=1)
    moon_line,  = ax.plot([], [], 'r-', linewidth=0.8)
    ax.legend(loc="upper right")
    ax.grid(True)

    frames_idx = list(range(0, len(df), frame_step))
    if frames_idx[-1] != len(df) - 1:
        frames_idx.append(len(df) - 1)

    def init():
        earth_dot.set_data([], [])
        moon_dot.set_data([], [])
        earth_line.set_data([], [])
        moon_line.set_data([], [])
        return earth_dot, moon_dot, earth_line, moon_line

    def update(i):
        idx = frames_idx[i]
        earth_dot.set_data([earth_x[idx]], [earth_y[idx]])
        moon_dot.set_data([scaled_moon_x[idx]], [scaled_moon_y[idx]])
        earth_line.set_data(earth_x[:idx+1], earth_y[:idx+1])
        moon_line.set_data(scaled_moon_x[:idx+1], scaled_moon_y[:idx+1])
        return earth_dot, moon_dot, earth_line, moon_line

    ani = FuncAnimation(fig, update, frames=len(frames_idx), init_func=init,
                        interval=50, blit=False)

    ani.save(gif_name, writer=PillowWriter(fps=30))


if __name__ == "__main__":
    main()
