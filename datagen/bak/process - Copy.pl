use v5.30;
use warnings;

my $what = 'corpus/*.txt';
my @letters = qw,\\ & | ^ [ ] ( ) ` < > { } ~ _ $ % - / = * + ! @ # . ; \, ' " ?,;
#("a" .. "z", ",", ".", "'", "\"", ";", ":", "?", "!", "(", ")");
my %mgrams;
my %bgrams;
# my %tgrams;

for (my $i = 0; $i <= $#letters; $i++) { 
	$mgrams{$letters[$i]} = 0;
	
	for (my $j = 0; $j <= $#letters; $j++) {
			
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
		s/\s[a-zA-Z]*\.//g;
		s/^[a-zA-Z]*\.//g;
		s/^[a-zA-Z]*\.//g;
		s/\s[a-zA-Z]*\?//g;
		s/^[a-zA-Z]*\?//g;
		s/\s[a-zA-Z]*://g;
		s/[a-zA-Z],//g;
		s/\)\.\s//g;
		s/--(-)+//g;
		s/^-(-)+//g;
		s/\s-(-)+//g;
#		s/[a-zA-Z]://g;
		s/[a-zA-Z]-//g;
		s/-[a-zA-Z]//g;
		s/\.\.(\.)+//g;
		s/\.\s\.//g;
		s/^>*//;
		s/^\$//;
		s/>>>//g;
		s/\d+\.\d+//g;
		s/\.\d+//g;
		s/\^\^(\^)*//;
		s/C#//;
		my $line = $_;
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
	my $key = $mgrams[$i];
	$key =~ s/\\/\\\\/;
	print lc "$key $mgrams{$mgrams[$i]}\n";
}
print "e 1
t 1
a 1
o 1
i 1
n 1
s 1
r 1
h 1
l 1
d 1
c 1
u 1
m 1
f 1
p 1
g 1
w 1
y 1
b 1
v 1
k 1
x 1
j 1
q 1
z 1";

close $out;
	
open($out, '>', "allDigraphs.txt") or die $!;
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

#open($out, '>', "allTrigraphs.txt") or die $!;
#select $out;
#for (my $i = 0; $i <= $#mgrams; $i++) {
#	print lc "$tgrams[$i] $tgrams{$tgrams[$i]}\n";
#}
#close $out;

sub by_mgrams { $mgrams{$b} <=> $mgrams{$a} }
sub by_bgrams { $bgrams{$b} <=> $bgrams{$a} }
#sub by_tgrams { $tgrams{$b} <=> $tgrams{$a} }