// Put all onload AJAX calls here, and event listeners
jQuery(document).ready(function () {
   
    jQuery.ajax({
        type: 'get',
        dataType: 'json',
        url: '/endpoint2',
        data: {},
        success: function (data) {

            // if (data.uploadStatus == false) {
            //     $('#fileUploadStatus').append("<h6>Error Upllading File</h6>");
            // }

            if (data.entries > 0) {
                var tableHeader = "<th>Image (Click To Download)</th>"
                tableHeader += "<th> File name (Click To Download)</th>"
                tableHeader += " <th>File Size</th>"
                tableHeader += "<th>Number Of Rectangles</th>"
                tableHeader += "<th>Number Of Circles</th>"
                tableHeader += "<th>Number Of Paths</th>"
                tableHeader += "<th>Number Of Groups</th>"
                $('#FileLogHead').append(tableHeader);
            }

            else {
                alert("No Entries Added");
                console.log("No Entries\n");
            }

            // File Log Heead
            for (let i = 0; i < data.entries; i++) {
                // File Log Body
                var addcontrols = "<tr>"
                addcontrols += "<td><a href =\"" + data.title[i] + "\">"
                addcontrols += "<img src=\"" + data.title[i] + "\"width=\"200\">"
                addcontrols += "</a></td>"
                addcontrols += "<td><a href =\"" + data.title[i] + "\"download>" + data.title[i] + "</a></td>"
                addcontrols += "<td>" + data.sizes[i] + "KB" + "</td>"
                addcontrols += "<td>" + data.numRectangle[i] + "</td>"
                addcontrols += "<td>" + data.numCircle[i] + "</td>"
                addcontrols += "<td>" + data.numPath[i] + "</td>"
                addcontrols += "<td>" + data.numGroup[i] + "</td>"
                addcontrols += "</tr>";
                // console.log(addcontrols);
                $('#FileLogBody').append(addcontrols);

                // DropDown menu

                var menuItem = "<li><input type=\"hidden\" value=\"" + i + "\" /><a href=\"#\">"

                menuItem += data.title[i]
                menuItem += "</a></li>";
                $('#SVGDropDown').append(menuItem)
            }


            $("#SVGDropDown li a").click(function () {

                // Clear The Last Selection Output
                $('#ViewPanelImage').html('');
                $('#ViewPanelTRTitleDesc').html('');
                $('#ViewPanelBodyTitleDesc').html('');
                $('#ViewPanelTRComponentsSummary').html('');
                $('#ViewPanelBodyComponentsSummary').html('');

                // Find Selection Index
                index = $(this).parent().find('input').val();

                // Image
                var imageRow = "<tr>"
                imageRow += "<td><img width=\"800\" src=\"" + data.title[index] + "\"</a></td>"
                imageRow += "</tr>";
                $('#ViewPanelImage').append(imageRow);

                // Title / Descritopn
                var titleDescTRRow = "<th>Title</th> <th>Description</th>"
                $('#ViewPanelTRTitleDesc').append(titleDescTRRow);
                var titleDescBodyRow = "<tr>"
                //titleDescBodyRow += "<td><a href =\"" + data.actualTitle[index] + "\"download>" + data.actualTitle[index] + "</a></td>"
                titleDescBodyRow += "<td>" + data.actualTitle[index] + "</td>"
                titleDescBodyRow += "<td>" + data.desc[index] + "</td>"
                titleDescBodyRow += "</tr>";
                $('#ViewPanelBodyTitleDesc').append(titleDescBodyRow);

                //Componnents Summay
                var ComponentsSummaryTRRow = "<th>Comonent</th> <th>Summary</th> <th>Other Attributes</th> <th>Attributes Summary</th>"
                $('#ViewPanelTRComponentsSummary').append(ComponentsSummaryTRRow);
                var ComponentsSummaryBodyRow = "<tr>"

                // Rectangles Summary
                var rectsData = JSON.parse(data.rectsComponentSum[index]);
                var rectsAttrData = JSON.parse(data.rectsAttrComponentSum[index]);

                //console.log(data.rectsAttrComponentSum[index]);

                for (var i = 0; i < rectsData.length; i++) {
                    var counter = rectsData[i];
                    let rectNum = i + 1;
                    ComponentsSummaryBodyRow += "<td>Rectangle " + rectNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + "Upper Left Corner: x = " + counter.x + counter.units + ", y = " + counter.y + counter.units + "<br/> Width = " + counter.w + counter.units + ", Height = " + counter.h + counter.units + "</td>"

                    var attr = "";
                    var object = rectsAttrData[i];
                    var isKey = true;

                    for (var j = 0; j < object.length; j++) {
                        for (var key in object[j]) {
                            if (isKey == true) {
                                attr += "Name: " + object[j][key];
                                isKey = false;
                            }
                            else {
                                attr += ", Value: " + object[j][key];
                                attr += "<br\>"
                                isKey = true;
                            }
                        }
                    }

                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td><td>" + attr + "</td>";
                    ComponentsSummaryBodyRow += "</tr>";
                }


                //  e Summary
                var circleData = JSON.parse(data.circlesComponentSum[index]);
                var cirleAttrData = JSON.parse(data.circlesAttrComponentSum[index]);

                for (var i = 0; i < circleData.length; i++) {
                    var counter = circleData[i];
                    let circleNum = i + 1;
                    ComponentsSummaryBodyRow += "<td> Circle : " + circleNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + "Centre: x = " + counter.cx + counter.units + ", y = " + counter.cy + counter.units + ", Radius = " + counter.r + counter.units + "</td>"


                    var attr = "";
                    var object = cirleAttrData[i];

                    var isKey = true;

                    for (var j = 0; j < object.length; j++) {
                        for (var key in object[j]) {
                            if (isKey == true) {
                                attr += "Name: " + object[j][key];
                                isKey = false;
                            }
                            else {
                                attr += ", Value: " + object[j][key];
                                attr += "<br\>"
                                isKey = true;
                            }
                        }
                    }

                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td><td>" + attr + "</td>";
                    ComponentsSummaryBodyRow += "</tr>";
                }

                // Path Summary 
                var pathData = JSON.parse(data.pathsComponentSum[index]);
                var pathAttrData = JSON.parse(data.pathsAttrComponentSummary[index]);

                for (var i = 0; i < pathData.length; i++) {
                    var counter = pathData[i];
                    let pathNum = i + 1;

                    var dataString = counter.d;
                    if (dataString.length > 64) {
                        dataString = dataString.substring(0, 64);
                    }

                    ComponentsSummaryBodyRow += "<td> Path : " + pathNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + "path data: x = " + dataString + "</td>"

                    var attr = "";
                    var object = pathAttrData[i];

                    var isKey = true;

                    for (var j = 0; j < object.length; j++) {
                        for (var key in object[j]) {
                            if (isKey == true) {
                                attr += "Name: " + object[j][key];
                                isKey = false;
                            }
                            else {
                                attr += ", Value: " + object[j][key];
                                attr += "<br\>"
                                isKey = true;
                            }
                        }
                    }

                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td><td>" + attr + "</td>";
                    ComponentsSummaryBodyRow += "</tr>";
                }

                // Group Summary 
                var groupData = JSON.parse(data.groupsComponentSum[index]);
                var groupAttrData = JSON.parse(data.groupsComponentAttrSummary[index]);
                for (var i = 0; i < groupData.length; i++) {
                    var counter = groupData[i];
                    let groupNum = i + 1;

                    ComponentsSummaryBodyRow += "<td> Group : " + groupNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + counter.children + " child elements" + "</td>"

                    var attr = "";
                    var object = groupAttrData[i];

                    var isKey = true;

                    for (var j = 0; j < object.length; j++) {
                        for (var key in object[j]) {
                            if (isKey == true) {
                                attr += "Name: " + object[j][key];
                                isKey = false;
                            }
                            else {
                                attr += ", Value: " + object[j][key];
                                attr += "<br\>"
                                isKey = true;
                            }
                        }
                    }

                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td><td>" + attr + "</td>";
                    ComponentsSummaryBodyRow += "</tr>";
                }

                $('#ViewPanelBodyComponentsSummary').append(ComponentsSummaryBodyRow);



                //*************************************************************
                // Name Desc Form

                $('#nameDescForm').html('');

                let NameDescString = "<hr/><hr/><hr/> <h3>Edit Title/Description</h3><br/>"
                NameDescString += "<div class=\"form-group\" id = \"nameDescInput\">"

                NameDescString += "<label for=\"nameBox\">" + "Edit File Name" + "</label>"
                NameDescString += "<input type=\"text\" class=\"form-control\" id =\"nameBox\"  value = \"" + data.actualTitle[index] + "\" placeholder =\"Placeholder\"/> </div>"

                NameDescString += "<label for=\"descBox\">" + "Edit Description" + "</label>"
                NameDescString += "<input type=\"text\" class=\"form-control\" id =\"descBox\"  value = \"" + data.desc[index] + "\" placeholder =\"Placeholder\"/> </div>"
                NameDescString += "<br/>"
                NameDescString += "<div class=\"form-group\"><input type =\"submit\" class=\"btn btn-secondary\"/></div>"
                $('#nameDescForm').append(NameDescString);


                // Event listener form example , we can use this instead explicitly listening for events
                // No redirects if possible
                $('#nameDescForm').submit(function (e) {
                    var newName = $('#nameBox').val();
                    var newDesc = $('#descBox').val();
                    console.log("Index name" + newName + "\n");
                    console.log("Index desc" + newDesc + "\n");
                    var theFile = data.title[index];

                    if (newName.length >= 256 || newDesc.length >= 256) {
                        console.log("New Name Error\n");
                    }

                    else {

                        jQuery.ajax({
                            type: 'get',            //Request type
                            dataType: 'json',       //Data type - we will use JSON for almost everything 
                            url: '/updateNameDescEndpoint',   //The server endpoint we are connecting to
                            data: {
                                name: newName,
                                desc: newDesc,
                                fileName: theFile
                            },
                            success: function (data) {

                                alert("Sucessfully Updated Data, Refresh Page To See Changes");

                                console.log("Sucessfully Updated Data");
                                e.preventDefault();

                            },
                            fail: function (error) {
                                console.log(error);
                            }
                        });
                    }
                });



                //*************************************************************
                // Rects Scaling  Form

                $('#rectsScalingForm').html('');

                let rectsScalingFormString = ""
                rectsScalingFormString += "<hr/><hr/><hr/><h3>Scale Rectangles</h3><br/><div class=\"form-group\" id = \"nameDescInput\">"

                rectsScalingFormString += "<label for=\"scaleBoxRects\">" + "Scale Rects Factor" + "</label>"
                rectsScalingFormString += "<input type=\"text\" class=\"form-control\" id =\"scaleBoxRects\" placeholder =\"Placeholder\"/> </div>"

                rectsScalingFormString += "<div class=\"form-group\"><input type =\"submit\" class=\"btn btn-secondary\"/></div>"
                $('#rectsScalingForm').append(rectsScalingFormString);


                // Event listener form example , we can use this instead explicitly listening for events
                // No redirects if possible
                $('#rectsScalingForm').submit(function (e) {
                    var newScale = $('#scaleBoxRects').val();

                    var theFile = data.title[index];

                    // if (newScale.isInteger()== false) {
                    if (newScale == '') {
                        alert('Please enter a whole number');
                        console.log("New scale Error\n");
                    }

                    else {

                        jQuery.ajax({
                            type: 'get',            //Request type
                            dataType: 'json',       //Data type - we will use JSON for almost everything 
                            url: '/updateRectsScaleEndpoint',   //The server endpoint we are connecting to
                            data: {
                                scale: newScale,
                                fileName: theFile
                            },
                            success: function (data) {

                                alert("Sucessfully Updated Data, Refresh Page To See Changes");
                                console.log("Sucessfully Updated Data");
                                e.preventDefault();

                            },
                            fail: function (error) {
                                console.log(error);
                            }
                        });
                    }
                });


                //*************************************************************
                // circles Scaling  Form

                $('#circlesScalingForm').html('');

                let circlesScalingFormString = ""
                circlesScalingFormString += "<hr/><hr/><hr/><h3>Scale Circles</h3><br/><div class=\"form-group\" id = \"nameDescInput\">"

                circlesScalingFormString += "<label for=\"scaleBox\">" + "Scale circles Factor" + "</label>"
                circlesScalingFormString += "<input type=\"text\" class=\"form-control\" id =\"scaleBox\" placeholder =\"Placeholder\"/> </div>"

                circlesScalingFormString += "<div class=\"form-group\"><input type =\"submit\" class=\"btn btn-secondary\"/></div>"
                $('#circlesScalingForm').append(circlesScalingFormString);


                // Event listener form example , we can use this instead explicitly listening for events
                // No redicircles if possible
                $('#circlesScalingForm').submit(function (e) {
                    var newScale = $('#scaleBox').val();

                    var theFile = data.title[index];

                    // if (newScale.isInteger()== false) {
                    if (newScale == '') {
                        alert('Please enter a whole number');
                        console.log("New scale Error\n");
                    }

                    else {

                        jQuery.ajax({
                            type: 'get',            //Request type
                            dataType: 'json',       //Data type - we will use JSON for almost everything 
                            url: '/updatecirclesScaleEndpoint',   //The server endpoint we are connecting to
                            data: {
                                scale: newScale,
                                fileName: theFile
                            },
                            success: function (data) {

                                alert("Sucessfully Updated Data, Refresh Page To See Changes");
                                console.log("Sucessfully Updated Data");
                                e.preventDefault();

                            },
                            fail: function (error) {
                                console.log(error);
                            }
                        });
                    }
                });




                //*************************************************************
                // add Rects  Form

                $('#addRectsForm').html('');

                let addRectsFormString = ""
                addRectsFormString += "<hr/><hr/><hr/><h3>Add Rectangle</h3><br/><div class=\"form-group\" id = \"nameDescInput\">"

                addRectsFormString += "<label for=\"scaleBoxRects\">" + "Upper Left Corner: x" + "</label>"
                addRectsFormString += "<input type=\"text\" class=\"form-control\" id =\"x\" placeholder =\"Placeholder\"/> </div>"

                addRectsFormString += "<label for=\"scaleBoxRects\">" + "Upper Left Corner: y" + "</label>"
                addRectsFormString += "<input type=\"text\" class=\"form-control\" id =\"y\" placeholder =\"Placeholder\"/> </div>"

                addRectsFormString += "<label for=\"scaleBoxRects\">" + "Width" + "</label>"
                addRectsFormString += "<input type=\"text\" class=\"form-control\" id =\"w\" placeholder =\"Placeholder\"/> </div>"

                addRectsFormString += "<label for=\"scaleBoxRects\">" + "Height" + "</label>"
                addRectsFormString += "<input type=\"text\" class=\"form-control\" id =\"h\" placeholder =\"Placeholder\"/> </div>"

                addRectsFormString += "<br/>"

                addRectsFormString += "<div class=\"form-group\"><input type =\"submit\" class=\"btn btn-secondary\"/></div>"
                $('#addRectsForm').append(addRectsFormString);


                // Event listener form example , we can use this instead explicitly listening for events
                // No redirects if possible
                $('#addRectsForm').submit(function (e) {
                    var x = $('#x').val();
                    var y = $('#y').val();
                    var width = $('#w').val();
                    var height = $('#h').val();

                    var theFile = data.title[index];

                    // if (newScale.isInteger()== false) {
                    if (x == '' || y == '' || width == '' || height == '') {
                        alert('Please Fill Out All VAlues');
                        console.log("New Rect Error\n");
                    }

                    else {

                        jQuery.ajax({
                            type: 'get',            //Request type
                            dataType: 'json',       //Data type - we will use JSON for almost everything 
                            url: '/addRectEndpoint',   //The server endpoint we are connecting to
                            data: {
                                newX: x,
                                newY: y,
                                newWidth: width,
                                newHeight: height,
                                fileName: theFile
                            },
                            success: function (data) {

                                alert("Sucessfully Updated Data, Refresh Page To See Changes");
                                console.log("Sucessfully Updated Data");
                                e.preventDefault();

                            },
                            fail: function (error) {
                                console.log(error);
                            }
                        });
                    }
                });

                //*************************************************************
                // add Circs  Form

                $('#addCirclesForm').html('');

                let addCirclesFormString = ""
                addCirclesFormString += "<hr/><hr/><hr/><h3>Add Circle</h3><br/><div class=\"form-group\" id = \"nameDescInput\">"

                addCirclesFormString += "<label for=\"scaleBoxRects\">" + "Center x" + "</label>"
                addCirclesFormString += "<input type=\"text\" class=\"form-control\" id =\"cx\" placeholder =\"Placeholder\"/> </div>"

                addCirclesFormString += "<label for=\"scaleBoxRects\">" + "Center y" + "</label>"
                addCirclesFormString += "<input type=\"text\" class=\"form-control\" id =\"cy\" placeholder =\"Placeholder\"/> </div>"

                addCirclesFormString += "<label for=\"scaleBoxRects\">" + "Radius" + "</label>"
                addCirclesFormString += "<input type=\"text\" class=\"form-control\" id =\"r\" placeholder =\"Placeholder\"/> </div>"

                addCirclesFormString += "<br/>"

                addCirclesFormString += "<div class=\"form-group\"><input type =\"submit\" class=\"btn btn-secondary\"/></div>"
                $('#addCirclesForm').append(addCirclesFormString);


                // Event listener form example , we can use this instead explicitly listening for events
                // No redirects if possible
                $('#addCirclesForm').submit(function (e) {
                    var cx = $('#cx').val();
                    var cy = $('#cy').val();
                    var r = $('#r').val();

                    var theFile = data.title[index];

                    // if (newScale.isInteger()== false) {
                    if (cx == '' || cy == '' || r == '') {
                        alert('Please Fill Out All Values');
                        console.log("New Rect Error\n");
                    }

                    else {

                        jQuery.ajax({
                            type: 'get',            //Request type
                            dataType: 'json',       //Data type - we will use JSON for almost everything 
                            url: '/addCircEndpoint',   //The server endpoint we are connecting to
                            data: {
                                newCX: cx,
                                newCY: cy,
                                newR: r,      
                                fileName: theFile
                            },
                            success: function (data) {
                                alert("Sucessfully Updated Data, Refresh Page To See Changes");
                                console.log("Sucessfully Updated Data");
                                e.preventDefault();
                            },
                            fail: function (error) {
                                console.log(error);
                            }
                        });
                    }
                });
            });
        },

        fail: function (error) {
            // Non-200 return, do something with error
            console.log(error);
        }
    });


});