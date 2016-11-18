#!/usr/bin/perl -w

use strict;
use POSIX qw(strftime);

my $max_minor = 199;
my $max_build = 1999;

my $date = strftime "%d.%m.%Y", localtime;
my @def_files = ( "src/general.h" );
my @doxy_files = ( "src/main.c" );

# Incrementing Source files with C defined Version Code
foreach my $f (@def_files) {
	my @new;
	open(F, "<$f") or die $!;
	my @content = <F>;
	my $major_set = 0;
	my $minor_set = 0;
	foreach my $line (@content) {
		if ($line =~ m/\#define.?VER_BUILD.?(\d+).*$/) {
			my $build = $1;
			$build++;
			if ($build > $max_build) {
				$build = 0;
				$minor_set = 1;
			}
			$line =~ s/(\#define.?VER_BUILD.?)\d+(.*)$/$1$build$2/;
		}
		elsif ($line =~ m/\#define.?VER_MINOR.?(\d+).*$/) {
			if ($minor_set > 0) {
				$minor_set = 0;
				my $minor = $1;
				$minor++;
				if ($minor > $max_minor) {
					$minor = 0;
					$major_set = 1;
				}
				$line =~ s/(\#define.?VER_MINOR.?)\d+(.*)$/$1$minor$2/;
			}
		} 
		elsif ($line =~ m/\#define.?VER_MAJOR.?(\d+).*$/) {
			if ($major_set > 0) {
				$major_set = 0;
				my $major = $1;
				$major++;
				$line =~ s/(\#define.?VER_MAJOR.?)\d+(.*)$/$1$major$2/;
			}
		}
		push(@new, $line);
	}
	close(F);
	open(F, ">$f") or die $!;
	foreach my $line (@new) {
		print F $line;
	}
	close(F);
}

# Incrementing Source files with doxygen commands with version and date
foreach my $f (@doxy_files) {
	my @new;
	open(F, "<$f") or die $!;
	my @content = <F>;
	foreach my $line (@content) {
		if ($line =~ m/^.*?\@version.?(\d+)\.(\d+)\.(\d+).*$/) {
			my $minor = $2;
			my $major = $1;
			my $build = $3;
			$build++;
			if ($build > $max_build) {
				$build = 0;
				$minor++;
				if ($minor > $max_minor) {
					$minor = 0;
					$major++;
				}
			}
			$line =~ s/^(.*?\@version.?)\d+\.\d+\.\d+(.*)$/$1$major\.$minor\.$build$2/;
		} elsif ($line =~ m/^.*?\@date.?\d+\/\d+\/\d+.*$/) {
			$line =~ s/^(.*?\@date.?)\d+\/\d+\/\d+(.*)$/$1$date$2/;
		}
		push(@new, $line);
	}
	close(F);
	open(F, ">$f") or die $!;
	foreach my $line (@new) {
		print F $line;
	}
	close(F);
}

#printf "Version Codes updated!\n";
