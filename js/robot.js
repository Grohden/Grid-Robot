(function () {
    'use strict';

    window.onload = function load() {
        var grid    = document.getElementById("canvas_container");
        var context = grid.getContext("2d");
        var gridCellSize = 100;
        const SPEED = 30;

        /**
         * Grid layout
         * @param {number} width - grid width
         * @param {number} height -  grid height
         * @param {number} [cellSize] -  grid cell size
         */
        function GridLayout(width, height,cellSize = 100) {
            this.bgColor = "blue";
            this.separatorColor = "red";
            this.height = height;
            this.width = width;

            var setBg = function setBg(color){
                if(!color){
                    throw new ReferenceError("Color is not defined");
                }
                __self.bgColor = color;
            };

            var getBg = function getBg(){
                return __self.bgColor;
            };

            var setSeparatorColor = function setSeparatorColor(color){
                if(!color){
                    throw new ReferenceError("Color is not defined");
                }
                __self.separatorColor = color;
            };

            var getSeparatorColor = function getSeparatorColor(){
                return __self.separatorColor;
            };

            /**
             * Paint the entire layout, including cols and lines.
             */
            var paintLayout = function paintLayout(){
                //Canvas bg
                context.fillStyle = "black";
                context.fillRect(0, 0, __self.width, __self.height);
                context.fill();

                drawColsAndLines();
            };

            /**
             * Draw the cols and lines of layout
             */
            var drawColsAndLines = function drawColsAndLines() {
                //Drawing line and cols
                context.strokeStyle = __self.separatorColor;
                context.lineWidth   = 5;
                context.beginPath();
                for (var x = 0; x <= __self.width / cellSize; x++) {

                    //Lines
                    context.moveTo(0, x * cellSize);
                    context.lineTo(__self.width, x * cellSize);
                    context.stroke();

                    //Cols
                    context.moveTo(x * cellSize, 0);
                    context.lineTo(x * cellSize, x * __self.height);
                    context.stroke();
                }
                context.closePath();
            };

            var __self = this;
            return{
                setBg: setBg,
                getBg: getBg,
                setSeparatorColor: setSeparatorColor,
                getSeparatorColor: getSeparatorColor,
                paintLayout:paintLayout,
                drawColsAndLines:drawColsAndLines
            }
        }
        var appLayout = new GridLayout(grid.width,grid.height);
        appLayout.paintLayout();
        console.log(appLayout);


        var circleRadius = 40;
        var circlePos = [gridCellSize/2,gridCellSize/2];


        var eraseLastPosition = function eraseLastPosition(){
            context.fillStyle = "black";
            circleRadius+=1;
            context.beginPath();
            context.arc(circlePos[0],circlePos[1],circleRadius,0,Math.PI*2,false);
            context.fill();
            circleRadius-=1;
            context.closePath();
        };

        setInterval(function interval() {

            context.fillStyle = "blue";
            context.beginPath();
            context.arc(circlePos[0],circlePos[1],circleRadius,0,Math.PI*2,false);
            context.fill();
            context.closePath();
        },SPEED);


        var move = function move(){

            var left = function(ignoreBounds){
                if(circlePos[0]>circleRadius || ignoreBounds) {
                    eraseLastPosition();
                    circlePos[0] -= gridCellSize;
                }
            };

            var right = function(ignoreBounds){
                if(circlePos[0]<grid.width-circleRadius || ignoreBounds) {
                    eraseLastPosition();
                    circlePos[0] += gridCellSize;
                }
            };

            var down = function(ignoreBounds){
                if(circlePos[1]<grid.height-circleRadius || ignoreBounds) {
                    eraseLastPosition();
                    circlePos[1] += gridCellSize;
                }
            };

            var up = function(ignoreBounds){
                if(circlePos[1]>circleRadius || ignoreBounds) {
                    eraseLastPosition();
                    circlePos[1] -= gridCellSize;
                }
            };

            return {
                left : left,
                right : right,
                down : down,
                up : up
            };
        }();


        window.onkeydown = function appKeys(event) {
            switch (event.key){
                case "ArrowRight":
                    move.right();
                    break;

                case "ArrowLeft":
                    move.left();
                    break;

                case "ArrowDown":
                    move.down();
                    break;

                case "ArrowUp":
                    move.up();
                    break;

                case "+":
                    circleRadius+=10;
                    break;

                case "-":
                    circleRadius-=10;
                    break;

            }
        }
    }
})();