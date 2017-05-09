// 
// Скрипт identicon строит изображение (иконку) по значению 
// хэша заданной строки.
// Иконка строится размера 7x7 пикселей и сохраняется в формате xpm.
// 
function about()
{
	console.log(
		"\nСкрипт identicon строит изображение (иконку) по значению хэша заданной строки.\n" +
		"Иконка строится размера 7x7 пикселей и сохраняется в формате xpm.\n" +
		"\nUsage:\n\t" +
		process.argv[1] + " <string to hash> <file to save xpm image>" +
		"\n\n"
		);
	process.exit(1);	
}

(function main() {
	if(process.argv.length < 4) about();

	var crypto = require('crypto');
	var name = process.argv[2];
	var hash = crypto.createHash('md5').update(name).digest('bin');

    var r = hash[0] & 255;
    var g = hash[1] & 255;
    var b = hash[2] & 255;
    var foregroundColour = "#" + r.toString(16) + g.toString(16) + b.toString(16);

    var t = (r + g + b) > 650 ? 128 : 255;
    var backgroundColour = "#" + t.toString(16) + t.toString(16) + t.toString(16);

    const fgp = '*';
    const bgp = '.';

	var pixels = [
		[bgp, bgp, bgp, bgp, bgp, bgp, bgp],
		[bgp, bgp, bgp, bgp, bgp, bgp, bgp],
		[bgp, bgp, bgp, bgp, bgp, bgp, bgp],
		[bgp, bgp, bgp, bgp, bgp, bgp, bgp],
		[bgp, bgp, bgp, bgp, bgp, bgp, bgp],
		[bgp, bgp, bgp, bgp, bgp, bgp, bgp],
		[bgp, bgp, bgp, bgp, bgp, bgp, bgp]
	];

    for(var x = 0; x < 3; ++x)
    {
        for(var y = 0; y < 5; ++y)
        {
            var i = x * 5 + y;
            if((hash[i] >> y & 1) == 1)
            {
                pixels[y+1][4-x+1] = pixels[y+1][x+1] = fgp;
            }
        }
    }

	var xpm = "static char* <variable_name>[] = {\" 7 7 2 1\"";
	xpm += ",\"" + fgp + " c " + foregroundColour + "\"";
	xpm += ",\"" + bgp + " c " + backgroundColour + "\"";
	for (var i = 0; i < 7; ++i) {
		xpm += ",\"" + pixels[i].join('') + "\"";		
	}
	xpm += "};";

	const xpmFileName = process.argv[3];

	var fs = require('fs');
	fs.writeFile(xpmFileName, xpm, function(error) {
		if (error) console.log(error.message);
	});

	setTimeout(()=>{console.log("Ok");}, 1000);
}
)();
