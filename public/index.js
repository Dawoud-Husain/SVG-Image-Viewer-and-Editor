// Put all onload AJAX calls here, and event listeners
jQuery(document).ready(function () {
    // On page-load AJAX Example
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/endpoint1',   //The server endpoint we are connecting to
        data: {
            data1: "Value 1",
            data2: 1234.56
        },
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
            jQuery('#blah').html("On page load, received string '" + data.somethingElse + "' from server");
            //We write the object to the console to show that the request was successful
            console.log(data);

        },
        fail: function (error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error);
        }
    });

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
                console.log("No Entries\n");
            }

            // File Log Heead
            for (let i = 0; i < data.entries; i++) {
                // File Log Body
                var addcontrols = "<tr>"
                addcontrols += "<td><img width=\"200\" src=\"" + data.title[i] + "\"</a></td>"
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
                titleDescBodyRow += "<td><a href =\"" + data.title[index] + "\"download>" + data.title[index] + "</a></td>"
                titleDescBodyRow += "<td>" + data.desc[index] + "</td>"
                titleDescBodyRow += "</tr>";
                $('#ViewPanelBodyTitleDesc').append(titleDescBodyRow);

                //Componnents Summay
                var ComponentsSummaryTRRow = "<th>Comonent</th> <th>Summary</th> <th>Other Attributes</th>"
                $('#ViewPanelTRComponentsSummary').append(ComponentsSummaryTRRow);
                var ComponentsSummaryBodyRow = "<tr>"

                // Rectangles Summary
                var rectsData = JSON.parse(data.rectsComponentSum[index]);
                for (var i = 0; i < rectsData.length; i++) {
                    var counter = rectsData[i];
                    let rectNum = i + 1;
                    ComponentsSummaryBodyRow += "<td>Rectangle " + rectNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + "Upper Left Corner: x = " + counter.x + counter.units + ", y = " + counter.y + counter.units + "<br/> Width = " + counter.w + counter.units + ", Height = " + counter.h + counter.units + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td>"
                    ComponentsSummaryBodyRow += "</tr>";
                }

                // Circle Summary
                var circleData = JSON.parse(data.circlesComponentSum[index]);
                for (var i = 0; i < circleData.length; i++) {
                    var counter = circleData[i];
                    let circleNum = i + 1;
                    ComponentsSummaryBodyRow += "<td> Circle : " + circleNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + "Centre: x = " + counter.cx + counter.units + ", y = " + counter.cy + counter.units + ", Radius = " + counter.r + counter.units + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td>"
                    ComponentsSummaryBodyRow += "</tr>";
                }

                // Path Summary 
                var pathData = JSON.parse(data.pathsComponentSum[index]);
                for (var i = 0; i < pathData.length; i++) {
                    var counter = pathData[i];
                    let pathNum = i + 1;

                    var dataString = counter.d;
                    if (dataString.length > 64) {
                        dataString = dataString.substring(0, 64);
                    }

                    ComponentsSummaryBodyRow += "<td> Path : " + pathNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + "path data: x = " + dataString + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td>"
                    ComponentsSummaryBodyRow += "</tr>";
                }

                // Group Summary 
                var groupData = JSON.parse(data.groupsComponentSum[index]);
                for (var i = 0; i < groupData.length; i++) {
                    var counter = groupData[i];
                    let groupNum = i + 1;

                    ComponentsSummaryBodyRow += "<td> Group : " + groupNum + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + counter.children + " child elements" + "</td>"
                    ComponentsSummaryBodyRow += "<td>" + counter.numAttr + "</td>"
                    ComponentsSummaryBodyRow += "</tr>";
                }

                $('#ViewPanelBodyComponentsSummary').append(ComponentsSummaryBodyRow);



                //*************************************************************
                // Editing Form


                let NameDescString = ""
                NameDescString += "<div class=\"form-group\" id = \"nameDescInput\">"

                NameDescString += "<label for=\"nameBox\">" + "Edit File Name" + "</label>"
                NameDescString += "<input type=\"text\" class=\"form-control\" id =\"nameBox\"  value = \"" + data.title[index] + "\" placeholder =\"Placeholder\"/> </div>"

                NameDescString += "<label for=\"descBox\">" + "Edit Description" + "</label>"
                NameDescString += "<input type=\"text\" class=\"form-control\" id =\"descBox\"  value = \"" + data.desc[index] + "\" placeholder =\"Placeholder\"/> </div>"

                NameDescString += "<div class=\"form-group\"><input type =\"submit\" class=\"btn btn-secondary\"/></div>"
                $('#someform').append(NameDescString);
            });
        },

        fail: function (error) {
            // Non-200 return, do something with error
            console.log(error);
        }
    });

    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
    $('#someform').submit(function (e) {
        var newName = $('#nameBox').val();
        var newDesc = $('#descBox').val();

        index = $("#SVGDropDown li a").parent().find('input').val();
        var theFile = data.title[index]

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
                    
                    console.log("Sucessfully Updated Data");
                    e.preventDefault();

                },
                fail: function (error) {
                    console.log(error);
                }
            });
        }



        // $('#blah').html("Form has data: " + );
        //e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
        });
    });
});