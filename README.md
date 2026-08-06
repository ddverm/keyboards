# keyboards

QMK configuration for my keyboards, using a [QMK userspace](https://docs.qmk.fm/newbs_external_userspace) so keymaps live in this repo instead of inside the `qmk_firmware` checkout.

## Setup

QMK firmware lives separately at `~/qmk_firmware` (a clone of `qmk/qmk_firmware`). This repo is registered as its userspace overlay:

```sh
qmk config user.overlay_dir="$(pwd)"
```

`qmk.json` at the repo root lists the build targets (keyboard:keymap pairs). Each keymap lives at `keyboards/<vendor>/<board>/keymaps/<name>/`, mirroring the layout QMK expects under `qmk_firmware/keyboards/`.

## Boards

### Keebio Iris CE, rev. 1

- QMK keyboard id: `keebio/iris_ce/rev1`
- Keymap: `drew` (`keyboards/keebio/iris_ce/rev1/keymaps/drew/`), seeded from the board's default keymap.

Compile:

```sh
qmk compile -kb keebio/iris_ce/rev1 -km drew
```

Flash (put the board in bootloader mode first — reset button on the back, or Bootmagic: hold top-left key while plugging in):

```sh
qmk flash -kb keebio/iris_ce/rev1 -km drew
```

Since these are set as the `qmk config` defaults, both commands also work bare (`qmk compile`, `qmk flash`).
