use v5.30;
use warnings;
use File::Find::Rule;

# Program settings

my $doCode = 0;
my $doTris = 0;
my $doLetters = 1;
my $lineLimitPerFiletype = 0;
my $debugMode = 1;

my $filterText = 1;
my $filterComments = 1;
my $filterASCIIArt = 1;
my $filterMiscBullshit = 1;

my @filetypesToProcess = qw( c h go bash sh rs pl pm py cs);
my $inputDirectory = './corpus/codecorpus/';
my $outPath = './';


# Program begins

my @filetypes;

for (my $i = 0; $i <= $#filetypesToProcess; $i++) {
	$filetypes[$i] = '*.' . $filetypesToProcess[$i];
}

my @subdirs = File::Find::Rule->directory->in( $inputDirectory );
my @files = File::Find::Rule->file()
                            ->name( @filetypes )
                            ->in( @subdirs );

my @symbols = qw,\\ & | [ ] ( ) ` < > { } ~ _ $ % - / = * + ! @ # . ; : \, ' " ? ^,;
#("a" .. "z", ",", ".", "'", "\"", ";", ":", "?", "!", "(", ")");
my @letters = ("a" .. "z");

my %mgrams;
my %bgrams;
my %tgrams;
my %mgramsLetters;
my $regex;
my $fname;
my $commentChars = "";

for (my $i = 0; $i <= $#symbols; $i++) { 
	$mgrams{$symbols[$i]} = 0;
	
	for (my $j = 0; $j <= $#symbols; $j++) {
			
			$bgrams{$symbols[$i] . $symbols[$j]} = 0;
			
			for (my $k = 0; $k <= $#symbols; $k++) {
				$tgrams{$symbols[$i] . $symbols[$j] . $symbols[$k]} = 0;
			}
	}
}

for (my $i = 0; $i <= $#letters; $i++) { 
	$mgramsLetters{$letters[$i]} = 0;
}

if ($filterText) {
#prepares, but does not yet use, a regex used in text filtering

	$regex = join "abc", @symbols;
	my @exclude = qw{. , ? ' " ( )};
	
	my $re2 = join "abc", @exclude;

	$re2 = quotemeta($re2);
#		$re2 =~ s/\\\(/\\s/g;
	$re2 = "($re2)";
	$re2 =~ s/abc/|/g;
	
	$regex =~ s/$re2/fmlr/g;
#		$regex =~ s/.fmlro.//g;
	$regex = quotemeta($regex);
	$regex = "($regex)";
	$regex =~ s/abc/|/g;

	print STDERR $regex;
}

foreach (@files) {
	my $p = 0;
	$fname = $_;

	open(my $in, '<', $_) or die $!;
	print STDERR "\n$_ \n";
	
	while(<$in>) {
		$p++;
		if ($debugMode) {
#			next if ($p < 500);
			last if ($p > 500);
			print STDERR "     In: $_";
		}
		
		print STDERR "$fname : $p\n" if ($p % 100 == 0);

		if ($filterText || $fname =~ /\.txt/) {	
			next unless (m/$regex/ || m/[a-zA-Z]\.[a-zA-Z]/ || m/[a-zA-Z]\([a-zA-Z]/ || m/[a-zA-Z\.](\d*)\(/);
			&filterComments;
			next if m/[a-zA-Z'\-]+\s[a-zA-Z'\-]+\s[a-zA-Z'\-]+\s[a-zA-Z'\-]+\s[a-zA-Z']/;
			&filterPunctuation;	
			next unless (m/$regex/ || m/[a-zA-Z]\.[a-zA-Z]/ || m/[a-zA-Z]\([a-zA-Z]/ || m/[a-zA-Z\.](\d*)\(/);
		}

		&filterMiscBullshit if ($filterMiscBullshit);
		&filterASCIIArt if ($filterASCIIArt);
		&filterComments if ($filterComments && !$filterText);
		print STDERR "****Out:$_" if ($debugMode);
		my $line = $_;
		
		while ( (my $key, my $value) = each %mgrams ) {
			my $qkey = quotemeta($key);
			my $count = () = $line =~ /$qkey/g;
			$mgrams{$key} += $count; #* $mult;
		}

		if ($doLetters) {
			while ( (my $key, my $value) = each %mgramsLetters ) {
				my $qkey = quotemeta($key);
				my $lcLine = lc $line;
				my $count = () = $lcLine =~ /$qkey/g;
				$mgramsLetters{$key} += $count; #* $mult;
			}
		}

		while ( (my $key, my $value) = each %bgrams ) {
			my $qkey = quotemeta($key);
			my $count = () = $line =~ /$qkey/g;
			$bgrams{$key} += $count; #* $mult;
		}	

		if($doTris) {	
			while ( (my $key, my $value) = each %tgrams ) {
				my $qkey = quotemeta($key);
				my $count = () = $line =~ /$qkey/g;
				$tgrams{$key} += $count; # * $mult;
			}
		}	
	}

}

my @mgrams = sort by_mgrams keys %mgrams;
my @mgramsLetters = sort by_mgramsLetters keys %mgramsLetters;
my @bgrams = sort by_bgrams keys %bgrams;
my @tgrams = sort by_tgrams keys %tgrams if $doTris;

if ($doLetters) {
	open(my $out, '>', $outPath . "allLetters.txt") or die $!;
	select $out;
	for (my $i = 0; $i <= $#mgramsLetters; $i++) {
		my $key = $mgramsLetters[$i];
		$key =~ s/\\/\\\\/;
		print lc "$key $mgramsLetters{$mgramsLetters[$i]}\n";
	}
	close $out;
}

open(my $out, '>', $outPath . "allChars.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#mgrams; $i++) {
	my $key = $mgrams[$i];
	$key =~ s/\\/\\\\/;
	print lc "$key $mgrams{$mgrams[$i]}\n";
}
close $out;
	
open($out, '>', $outPath . "allDigraphs.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#bgrams; $i++) {
	my $key = $bgrams[$i];
	
	if ($key =~ m/\\\\/) {
		$key =~ s/\\\\/\\\\\\\\/;
	} else {
		$key =~ s/\\/\\\\/;
	}
	
	print lc "$key $bgrams{$bgrams[$i]}\n";
}
close $out;

if ($doTris) {
	open($out, '>', $outPath . "allTrigraphs.txt") or die $!;
	select $out;
	for (my $i = 0; $i <= $#tgrams; $i++) {
		my $key = $tgrams[$i];
		
		if ($key =~ m/\\\\/) {
			$key =~ s/\\\\/\\\\\\\\/;
		} else {
			$key =~ s/\\/\\\\/;
		}

		print lc "$key $tgrams{$tgrams[$i]}\n";
	}
	close $out;
}

sub by_mgrams { $mgrams{$b} <=> $mgrams{$a} }
sub by_mgramsLetters { $mgramsLetters{$b} <=> $mgramsLetters{$a} }
sub by_bgrams { $bgrams{$b} <=> $bgrams{$a} }
sub by_tgrams { $tgrams{$b} <=> $tgrams{$a} }

sub filterMiscBullshit {
	s/.*\[assembly.*//;
	s/\\...\\...\\...\\...\\....*//;
#	s/.x..,.x..,.x..,.x..,.*//;
}

sub filterASCIIArt {
	s/====+/ /g;
	s/```+/ /g;
	s/~~~+/ /g;
	s/\*\*\*+/ /g;
	s/--(-)+/ /g;
	s/^-(-)+/ /g;
	s/\s-(-)+/ /g;
	s/\.\.(\.)+/ /g;
	s/\.\s\./ /g;
	s/^>*/ /;
	s/^\$/ /;
	s/>>>/ /g;
	s/\^\^(\^)*/ /;
}

sub filterPunctuation {
	s/\s[a-zA-Z]*:\s/ /g;
	s/\)\.\s/ /g;
	s/[a-zA-Z]-[a-zA-Z]/ /g;
	s/\d+\.\d+/ /g;
	s/\.\d+/ /g;
	s/C#/ /;
	s/[a-zA-Z]*\.\s//g;
	s/[a-zA-Z]*\.$//;
	s/[a-zA-Z]*\?\s//g;
	s/[a-zA-Z]*\?$//g;
}

sub filterComments {
	&filterOneLineComments;
	if ($fname =~ /\.c$/ || $fname =~ /\.h$/ || $fname =~ /\.cs$/ || $fname =~ /\.go$/) {
		s/^\s*\*\s.*//;
		s/\/\*.*/\/*/;
		s/.*\/\*/*\//;
	}
}

sub filterOneLineComments {
	if ($fname =~ /\.rs$/ || $fname =~ /\.c$/ || $fname =~ /\.h$/ || $fname =~ /\.cs$/ || $fname =~ /\.go$/) {
		$commentChars = '\/\/';
	} elsif ($fname =~ /\.pl$/ || $fname =~ /\.pm$/ || $fname =~ /\.bash$/ || $fname =~ /\.sh$/ || $fname =~ /\.py$/) {
		$commentChars = '#';
	} else {
		$commentChars = '[#|\/\/]';
	}
	s/(.*)([^\\])(${commentChars}).*/$1$2$3/;
	s/^(${commentChars}).*/$1/;
}