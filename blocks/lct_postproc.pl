use strict;

open(FILE, "<sfun_GPIOSetup.tlc") || die "File not found";
my @lines = <FILE>;
close(FILE);

my @newlines;
foreach(@lines) {
   $_ =~ s/Outputs/Start/g;
   push(@newlines,$_);
}

open(FILE, ">sfun_GPIOSetup.tlc") || die "File not found";
print FILE @newlines;
close(FILE);
