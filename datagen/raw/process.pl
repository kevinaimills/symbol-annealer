use v5.30;
use warnings;

my $what = 'norvig.txt';
my @letters = ("A" .. "Z");
my %firstLetters;
my %lastLetters;

# for (my $i = 0; $i <= $#letters; $i++) { 
# 	$mgrams{$letters[$i]} = 0;
	
# 	for (my $j = 0; $j <= $#letters; $j++) {
# 			$bgrams{$letters[$i] . $letters[$j]} = 0;
			
# 			for (my $k = 0; $k <= $#letters; $k++) {
# 				$tgrams{$letters[$i] . $letters[$j] . $letters[$k]} = 0;
# 			}
# 	}
# }



my @toProcess = glob $what;
foreach (@toProcess) {
	my $p = 1;
	open(my $in, '<', $_) or die $!;
	while(<$in>) {
		print STDERR "$p - ";
		$p++;
		my $line = $_;
		my $mult = 0;
		my $fletter;
		my $lletter;
		my $num;
		if ($p < 100 && /^([A-Z])\s(\d+)/) {
			$fletter = $1;
			$lletter = $1;
			$num = $2;

			$mult = $num / 1000;
			$mult = int($mult + 0.5);

			$firstLetters{$fletter} += $mult;
			$lastLetters{$lletter} += $mult;
		} elsif (/^([A-Z]).*([A-Z])\s(\d+)/) {
			$fletter = $1;
			$lletter = $2;
			$num = $3;

			$mult = $num / 1000;
			$mult = int($mult + 0.5);

			$firstLetters{$fletter} += $mult;
			$lastLetters{$lletter} += $mult;
		} 


		
	# 	while ( (my $key, my $value) = each %mgrams ) {
	# 		my $count = () = $line =~ /$key/g;
	# 		$mgrams{$key} += $count * $mult;
	# 	}

	# 	while ( (my $key, my $value) = each %bgrams ) {
	# 		my $count = () = $line =~ /$key/g;
	# 		$bgrams{$key} += $count * $mult;
	# 	}	

	# 	while ( (my $key, my $value) = each %tgrams ) {
	# 		my $count = () = $line =~ /$key/g;
	# 		$tgrams{$key} += $count * $mult;
	# 	}		
	}

}

my @firstLetters = sort by_firstLetters keys %firstLetters;
my @lastLetters = sort by_lastLetters keys %lastLetters;
# my @tgrams = sort by_tgrams keys %tgrams;

open(my $out, '>', "allFirst.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#firstLetters; $i++) {
	print lc "$firstLetters[$i] $firstLetters{$firstLetters[$i]}\n";
}

close $out;
	
open($out, '>', "allLast.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#lastLetters; $i++) {
	print lc "$lastLetters[$i] $lastLetters{$lastLetters[$i]}\n";
}
close $out;

# open($out, '>', "allTrigraphs.txt") or die $!;
# select $out;
# for (my $i = 0; $i <= $#tgrams; $i++) {
# 	print lc "$tgrams[$i] $tgrams{$tgrams[$i]}\n";
# }
# close $out;

sub by_firstLetters { $firstLetters{$b} <=> $firstLetters{$a} }
sub by_lastLetters { $lastLetters{$b} <=> $lastLetters{$a} }
# sub by_tgrams { $tgrams{$b} <=> $tgrams{$a} }