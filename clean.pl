#!/usr/bin/perl
use 5.12.0;
use warnings FATAL => 'all';

my @files = `find 3650* -type f`;

for my $file (@files) {
    $file =~ /^.git/ && next;

    chomp $file;
    my $type = `file "$file"`;
    chomp $type;

    if ($type =~ /ELF/ && $file !~ /ASCII/) {
        say "Cleaning: $file";
        system(qq{rm "$file"});
    }
}
