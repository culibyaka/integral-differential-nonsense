#!/usr/bin/env python3
from collections.abc import Callable
from functools import wraps
from pathlib import Path
from typing import TypedDict
import matplotlib
import matplotlib.pyplot as plt
from argparse import ArgumentParser
import io
import sys
from csv import DictReader


ROOT = Path(__file__).resolve().parent.parent
CONFIG_PATH = ROOT / "config"
PLOT_OUT_PATH = ROOT / "plot"
PLT_BACKEND = "QtAgg"

PLOT_OUT_PATH.mkdir(parents=True, exist_ok=True)


def use_nan(func: Callable[[float], float]) -> Callable[[float], float]:
    @wraps(func)
    def wrapper(x: float) -> float:
        try:
            return func(x)
        except ValueError:  # type: ignore
            return float("nan")

    return wrapper


class Tabulature(TypedDict):
    x: list[float]
    f: list[float]


def read_csv(fp: io.FileIO) -> Tabulature:
    reader = DictReader(fp)
    mapping = {"x": [], "f": []}
    for line in reader:
        mapping["x"].append(float(line["x"]))
        mapping["f"].append(float(line["f"]))
    return mapping


def plot(data: Tabulature,interactive: bool) -> None:
    if interactive:
        matplotlib.use(PLT_BACKEND)

    plt.plot(data["x"], data["f"])
    plt.legend()

    if interactive:
        plt.show()
    else:
        plt.savefig(PLOT_OUT_PATH / "plot.png")


def run(data: Path, interactive: bool) -> None:
    with data.open("r") as fp:
        tab = read_csv(fp)

    plot(tab, interactive)


def main() -> int:
    parser = ArgumentParser()
    parser.add_argument("data", type=Path)
    parser.add_argument("-s", "--step", type=float, default=None)
    parser.add_argument("-i", "--interactive", action="store_true")
    args = parser.parse_args()

    # try:
    run(args.data, args.interactive)
    # except Exception as exc:
    #     print(exc)
    #     return -1
    return 0


if __name__ == "__main__":
    sys.exit(main())
