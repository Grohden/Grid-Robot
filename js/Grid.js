var Grid = (function () {
    function Grid(element_or_id, cols, rows) {
        this.element_or_id = element_or_id;
        this.cols = cols;
        this.rows = rows;
        if (typeof element_or_id === 'string') {
            this.init(element_or_id);
        }
        else {
            element_or_id.appendChild(this.init(null));
        }
    }
    Grid.prototype.init = function (id) {
        var table;
        if (id == null) {
            table = document.createElement("table");
        }
        else {
            table = document.getElementById(id);
            alert(table);
        }
        for (var x = 0; x < this.cols; x++) {
            var col = document.createElement("tr");
            for (var y = 0; y < this.rows; y++) {
                var td = document.createElement("td");
                td.textContent = y.toString();
                col.appendChild(td);
            }
            table.appendChild(col);
        }
        return table;
    };
    return Grid;
})();
function create() { var t = new Grid("grid", 5, 5); }
