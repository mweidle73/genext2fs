# genext2fs GitHub maintenance environment

This repository mirrors the authoritative
[`bestouff/genext2fs`](https://github.com/bestouff/genext2fs) history and
maintains the private library interface consumed by
[Abuild](https://github.com/mweidle73/abuild).

The long-lived branches have distinct roles:

- `master` mirrors the authoritative upstream `master` branch;
- `genext2fs-abuild` permanently preserves the legacy commit graph so old
  Abuild gitlinks, including `1578cc89`, remain fetchable;
- `abuild` carries the same Abuild adaptations rebased onto the equivalent
  upstream commit `b93dd96f`;
- `abuild-gh` adds only files below `.github/` to `abuild`.

The old and new Abuild tips deliberately have different commit identifiers but
the same Git tree. The legacy branch must not be force-updated or deleted.

Run the complete Trixie build, upstream regression suite, Abuild embedding-API
probe, sanitizer pass and informative source-coverage report with:

```sh
.github/ci/run .github/ci/check
```

Build the Pages site with:

```sh
.github/ci/run .github/ci/build-pages
```

With no command, `run` opens an interactive non-root shell in `/work`:

```sh
.github/ci/run
```

The launcher disables networking after building the image, uses a read-only
container root filesystem and mounts only this checkout read-write at `/work`.
Set `GENEXT2FS_CI_IMAGE` to override the image name and `DOCKER_PLATFORM` to
override the default `linux/amd64` platform.
