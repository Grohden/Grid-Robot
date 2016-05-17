class Grid{
        constructor(public element_or_id:HTMLElement|string, public cols:number, public rows:number) {
                if(typeof element_or_id=== 'string'){
                        this.init(element_or_id);
                } else {
				(<HTMLElement>element_or_id).appendChild(this.init(null));
				}
                       
        }       
       
        init(id:string){
                var table:HTMLElement;
                if(id==null){
                        table=document.createElement("table");
                } else {table=document.getElementById(id);alert(table);}
               
                for (var x=0;x<this.cols;x++){
                        var col=document.createElement("tr");
                        for(var y=0;y<this.rows;y++){
                                var td=document.createElement("td");
                                td.textContent=y.toString();
                                col.appendChild(td);
                        }
                        table.appendChild(col);                                        
                }
                return table;
        }       
}

function create(){var t=new Grid("grid",5,5);}
