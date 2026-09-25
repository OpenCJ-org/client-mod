"""Compile tintable/palette arrow materials from the legacy DXT5 arrow.

Retain every alpha block and color index (including mipmaps and the outline).
Only convert RGB565 endpoints; no resampling or new arrow artwork is involved.
Run from any directory with Python 3. Output is consumed by existing makeMod.py.
"""
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1] / "cod4"
PALETTE = {"tint": (255,255,255), "aqua": (0,204,255),
           "lime": (0,255,0), "gold": (255,255,0), "orng": (255,136,0),
           "soft": (255,119,119), "dark": (170,0,0),
           "lila": (170,85,255), "pink": (255,119,204)}

def compile_arrow(name, rgb):
    image = bytearray((ROOT / "images/opencj_checkpoint_blue.iwi").read_bytes())
    if image[:4] != b"IWi\x06" or image[4] != 13 or (len(image)-28) % 16:
        raise ValueError("Expected legacy CoD4 DXT5 arrow")
    for block in range(28, len(image), 16):
        for offset in (block+8, block+10):
            color = struct.unpack_from("<H", image, offset)[0]
            peak = max(((color>>11)&31)/31, ((color>>5)&63)/63, (color&31)/31)
            peak = min(1, peak * 255/250)
            r,g,b = (round(v*peak) for v in rgb)
            struct.pack_into("<H", image, offset, ((r*31//255)<<11)|((g*63//255)<<5)|(b*31//255))
    (ROOT / ("images/opencj_checkpoint_"+name+".iwi")).write_bytes(image)
    # Equal-length names preserve the legacy compiled material offsets.
    assert len(name)==4
    for suffix in ("", "_obj"):
        material = (ROOT / ("materials/opencj_checkpoint_blue"+suffix)).read_bytes()
        material = material.replace(b"opencj_checkpoint_blue", ("opencj_checkpoint_"+name).encode())
        (ROOT / ("materials/opencj_checkpoint_"+name+suffix)).write_bytes(material)

if __name__ == "__main__":
    for name,rgb in PALETTE.items():
        compile_arrow(name,rgb)
    print("Compiled",len(PALETTE),"legacy-arrow material variants")
