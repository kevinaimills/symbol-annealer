use v5.30;
use warnings;

my $what = '../../../corpus/punc/*.txt';
my @letters = ("a" .. "z", ",", ".", "'", "\"", ";", ":", "?", "!", "(", ")");
my %mgrams;
my %bgrams;
# my %tgrams;

for (my $i = 0; $i <= $#letters; $i++) { 
	$mgrams{$letters[$i]} = 0;
	
	for (my $j = 0; $j <= $#letters; $j++) {
			$_ = $letters[$i] . $letters[$j];
			
#			if (!(m/(he|it|sh)/)) {
				next if m/[a-z][a-z]/;
				next if m/[.,;:!?][a-z]/;
				next if m/[a-z][\(\)]/;
#			} 
			
			$bgrams{$letters[$i] . $letters[$j]} = 0;
			
#			for (my $k = 0; $k <= $#letters; $k++) {
#				$tgrams{$letters[$i] . $letters[$j] . $letters[$k]} = 0;
#			}
	}
}



my @toProcess = glob $what;
foreach (@toProcess) {
	my $p = 1;
	open(my $in, '<', $_) or die $!;
	while(<$in>) {
		print STDERR "$p - ";
		$p++;
		my $line = lc $_;
#		my $mult = 0;
		
#		m/\s(\d+)/;
#		$mult = $1 / 1000;
#		$mult = int($mult + 0.5);
		
		while ( (my $key, my $value) = each %mgrams ) {
			my $qkey = quotemeta($key);
			my $count = () = $line =~ /$qkey/g;
			$mgrams{$key} += $count; #* $mult;
		}

		while ( (my $key, my $value) = each %bgrams ) {
			my $qkey = quotemeta($key);
			my $count = () = $line =~ /$qkey/g;
			$bgrams{$key} += $count; #* $mult;
		}	

#		while ( (my $key, my $value) = each %tgrams ) {
#			my $count = () = $line =~ /$key/g;
#			$tgrams{$key} += $count * $mult;
#		}		
	}

}

my @mgrams = sort by_mgrams keys %mgrams;
my @bgrams = sort by_bgrams keys %bgrams;
#my @tgrams = sort by_tgrams keys %tgrams;

open(my $out, '>', "allChars.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#mgrams; $i++) {
	print lc "$mgrams[$i] $mgrams{$mgrams[$i]}\n";
}

close $out;
	
open($out, '>', "allDigraphs.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#bgrams; $i++) {
	print lc "$bgrams[$i] $bgrams{$bgrams[$i]}\n";
}
close $out;

#open($out, '>', "allTrigraphs.txt") or die $!;
#select $out;
#for (my $i = 0; $i <= $#mgrams; $i++) {
#	print lc "$tgrams[$i] $tgrams{$tgrams[$i]}\n";
#}
#close $out;

sub by_mgrams { $mgrams{$b} <=> $mgrams{$a} }
sub by_bgrams { $bgrams{$b} <=> $bgrams{$a} }
#sub by_tgrams { $tgrams{$b} <=> $tgrams{$a} }