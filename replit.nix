{ pkgs }: {
	deps = [
   pkgs.gh
   pkgs.cloc
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}