with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "asus-driver-touchpad";
    buildInputs = [ pkg-config cmake libevdevc ];
}