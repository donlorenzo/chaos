var cells;
var canvas;
var cell_size;
var w, h;
var rule;


function getBit(byte, bit) {
    return byte & (1<<bit);
}

function hideThrobber() {
    throbber = document.getElementById("throbber");
    throbber.style.visibility = "hidden";
}

function showThrobber() {
    throbber = document.getElementById("throbber");
    throbber.style.visibility = "visible";
}

function onInit() {
    canvas = document.getElementById("mycanvas");
    canvas.addEventListener("mousedown", onMouseDown, false);
    hideThrobber();
    reset();
}

function drawLine(ctx, from_x, from_y, to_x, to_y) {
    ctx.beginPath();
    ctx.moveTo(from_x, from_y);
    ctx.lineTo(to_x, to_y);
    ctx.stroke();
}

function reset() {
    canvas = document.getElementById("mycanvas");
    ctx = canvas.getContext("2d");
    cell_size = document.getElementById("cell_size").value;
    w = document.getElementById("width").value * cell_size;
    h = document.getElementById("height").value * cell_size;
    rule = document.getElementById("rule").value;
    c = document.getElementById("mycanvas");
    c.width = w;
    c.height = h;
    drawRaster(ctx);
    window.cells = new Array(h);
    for (var i = 0; i < h; i++) {
        window.cells[i] = new Array(w);
        for (var j = 0; j < w; j++) {
            window.cells[i][j] = false;
        }
    }
}

function getMousePos(evt) {
    var rect = canvas.getBoundingClientRect();
    return { x: evt.clientX - rect.left, 
             y: evt.clientY - rect.top };
}

function onMouseDown(event) {
    pos = getMousePos(event);
    cell = { x: Math.floor(pos.x/cell_size),
             y: Math.floor(pos.y/cell_size) };
    cells[cell.y][cell.x] = !(cells[cell.y][cell.x]);
    var ctx = canvas.getContext("2d");
    updateCell(ctx, cell.x, cell.y);
    refresh();
}

function calcRow(y) {
    prev_row = cells[y-1];
    row = cells[y];
    for(var x = 0; x < w; x++) {
        var pattern = 0;
        if (x!=0 && x!=w-1) {
            pattern = ((prev_row[x-1] << 2) |
                       (prev_row[x]   << 1) |
                       (prev_row[x+1] << 0));
        } else if (x==0) {
            pattern = ((prev_row[x]   << 1) |
                       (prev_row[x+1] << 0));
        } else if (x==w-1) {
            pattern = ((prev_row[x-1] << 2) |
                       (prev_row[x]   << 1));
        }
        if ((getBit(rule, 0) && pattern == 0) ||
            (getBit(rule, 1) && pattern == 1) ||
            (getBit(rule, 2) && pattern == 2) ||
            (getBit(rule, 3) && pattern == 3) ||
            (getBit(rule, 4) && pattern == 4) ||
            (getBit(rule, 5) && pattern == 5) ||
            (getBit(rule, 6) && pattern == 6) ||
            (getBit(rule, 7) && pattern == 7)) {
            row[x] = true;
        } else {
            row[x] = false;
        }
    }
}

function refresh_async() {
    showThrobber();
    function doit(y) {
        calcRow(y);
        if (y+1 < cells.length) {
            // loop condition
            setTimeout(function() {doit(y+1);}, 0);
        } else {
            // end condition
            var ctx = canvas.getContext("2d");
            draw(ctx);
            hideThrobber();
        }
    }
    setTimeout(function(){doit(1);}, 0);
}

function refresh_sync() {
    showThrobber();
    for(var y = 1; y < h; y++) {
        calcRow(y);
    }
    var ctx = canvas.getContext("2d");
    draw(ctx);
    hideThrobber();
}

function refresh() {
    refresh_async();
//    refresh_sync();
}

function updateCell(ctx, x, y) {
    if (cells[y][x]) {
        ctx.fillStyle = "#FF0000";
    } else {
        ctx.fillStyle = "#FFFFFF";
    }
    ctx.fillRect(x*cell_size, y*cell_size, cell_size, cell_size);
    drawRaster(ctx);
} 

function drawRaster(ctx) {
    for( var y = 0; y < h; y++ ) {
        drawLine(ctx, 0, y*cell_size, w, y*cell_size);
    }
    for(var x = 0; x < w; x++) {
        drawLine(ctx, x*cell_size, 0, x*cell_size, h);
    }
}

function draw(ctx) {
    var maxY = cells.length;
    var maxX = cells[0].length;
    // clear the canvas
    ctx.fillStyle = "#FFFFFF";
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // draw live calles
    ctx.fillStyle = "#FF0000";
    for (var y = 0;  y < maxY; y++) {
        for (var x = 0;  x < maxX; x++) {
            if (cells[y][x]) {
                ctx.fillRect(x*cell_size, y*cell_size, cell_size, cell_size);
            }
        }
    }
    // overlay with raster
    drawRaster(ctx);
}
