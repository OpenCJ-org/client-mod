# Route finish audio

The two MP3s in this directory were supplied by the OpenCJ owner for this feature.
Their filenames retain the creator names and source IDs. No separate license
text was supplied with them.

- `freesound_gamestudio-level-complete-394515.mp3`: ordinary route completion.
- `universfield-victory-fanfare-152480.mp3`: new top-three time or low-RPG finish.

Run `python3 dev-tools/scripts/build-finish-sounds.py` from the workspace on the
server to regenerate the WAV assets (requires libsndfile with MP3 support).
The converter never amplifies the source, caps peaks at -6 dBFS and RMS at
-20 dBFS, and outputs 44.1 kHz 16-bit PCM. `opencj_finish.csv` applies a further
50% volume using the interface volume group. These are loaded 2D sounds embedded
in `mod.ff`, played locally only to the finisher.

Ranking follows the existing mode-inclusion rules and uses one best run per
player on each board. Time is ordered by time then RPGs; low-RPG by RPGs then
time. Exact ties retain the older run, so repeating an existing result does not
create another record fanfare. Any of a route's finish checkpoints can qualify.
