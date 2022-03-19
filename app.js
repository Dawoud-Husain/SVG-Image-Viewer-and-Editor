'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app = express();
const path = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname + '/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');
const { exit } = require('process');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/', function (req, res) {
  res.sendFile(path.join(__dirname + '/public/index.html'));
});

// Send Style, do not change
app.get('/style.css', function (req, res) {
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname + '/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js', function (req, res) {
  fs.readFile(path.join(__dirname + '/public/index.js'), 'utf8', function (err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, { compact: true, controlFlowFlattening: true });
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function (req, res) {
  if (!req.files) {
    return res.status(400).send('No files were uploaded.');
  }

  let uploadFile = req.files.uploadFile;

  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function (err) {
    if (err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function (req, res) {
  fs.stat('uploads/' + req.params.name, function (err, stat) {
    if (err == null) {
      res.sendFile(path.join(__dirname + '/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: ' + err);
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 

let sharedLib = ffi.Library('./libsvgparser.so', {
 
  'isValidSVGFromFile': ['bool', ['string', 'string']],
  'getFileSize': ['int', ['string']],
  'getNumsFromFile' : ['string', ['string', 'string']],

  'getSVGDescription': ['string', ['string', 'string']],
  'getSVGTitle': ['string', ['string', 'string']],

  'getRectsImmediateChildrenSummary': ['string', ['string', 'string']],
  'getRectsAttrImmediateChildrenSummary': ['string', ['string', 'string']],

  'getCirclesImmediateChildrenSummary': ['string', ['string', 'string']],
  'getCircsAttrImmediateChildrenSummary': ['string', ['string', 'string']],

  'getPathsImmediateChildrenSummary': ['string', ['string', 'string']],
  'getPathsAttrImmediateChildrenSummary': ['string', ['string', 'string']],

  'getGroupsImmediateChildrenSummary': ['string', ['string', 'string']],
  'getGroupsAttrImmediateChildrenSummary': ['string', ['string', 'string']],

  'updateSVGNameDesc': ['bool', ['string', 'string', 'string', 'string'] ],


  'scaleRect': ['bool', ['string', 'string', 'int']],
  'scaleCirc': ['bool', ['string', 'string', 'int']],


  'addRect': ['bool', ['string', 'string', 'float', 'float', 'float', 'float']],
  'addCirc': ['bool', ['string', 'string', 'float', 'float', 'float']]
});



//Sample endpoint
app.get('/endpoint1', function (req, res) {
  let retStr = req.query.data1 + " " + req.query.data2;

  res.send(
    {
      somethingElse: retStr
    }
  );
});



app.get('/endpoint2', function (req, res) {
  //let retStr = req.query.data1 + " " + req.query.data2;

  let retStr = "";
  let numEntries = 0;

  let titles = [];
  let fileSizes = [];

  let numRects = [];
  let numCircles = [];
  let numPaths = [];
  let numGroups = [];

  let actualTitles = [];
  let descriptors = []; 

  let rectsComponentSummary = [];
  let circlesComponentSummary = []; 
  let pathsComponentSummary = [];
  let groupsComponentSummary = [];

  let rectsComponentAttrSummary = [];
  let circlesComponentAttrSummary = [];
  let pathsComponentAttrSummary = [];
  let groupsComponentAttrSummary = [];

  let sucessValue = true;



  const fs2 = require("node:fs/promises");

  fs.readdir("./uploads", { withFileTypes: true }, (err, files) => {
      //console.log("./uploads");
      if (err) {
        console.log(err);
      }

      else {
        files.forEach(file => {

          let svgFileName = 'uploads/' + file.name;
          let thing = sharedLib.isValidSVGFromFile(svgFileName, 'svg.xsd');

          if (thing == false) {
            sucessValue = false;
            console.log(file.name + ' is invalid\n');
          }

          else {

            retStr += file.name + "\n";

            titles[numEntries] = file.name;
            fileSizes[numEntries] = sharedLib.getFileSize(svgFileName);
            
            let text = sharedLib.getNumsFromFile(svgFileName, 'svg.xsd');
            const nums = JSON.parse(text);

            numRects[numEntries] = nums.numRect;
            numCircles[numEntries] = nums.numCirc;
            numPaths[numEntries] = nums.numPaths;
            numGroups[numEntries] = nums.numGroups;

            actualTitles[numEntries] = sharedLib.getSVGTitle(svgFileName, 'svg.xsd');
            descriptors[numEntries] = sharedLib.getSVGDescription(svgFileName, 'svg.xsd');
      
            rectsComponentSummary[numEntries] = sharedLib.getRectsImmediateChildrenSummary(svgFileName, 'svg.xsd');
            circlesComponentSummary[numEntries] = sharedLib.getCirclesImmediateChildrenSummary(svgFileName, 'svg.xsd');
            pathsComponentSummary[numEntries] = sharedLib.getPathsImmediateChildrenSummary(svgFileName, 'svg.xsd');
            groupsComponentSummary[numEntries] = sharedLib.getGroupsImmediateChildrenSummary(svgFileName, 'svg.xsd');

            rectsComponentAttrSummary[numEntries] = sharedLib.getRectsAttrImmediateChildrenSummary(svgFileName, 'svg.xsd');
            circlesComponentAttrSummary[numEntries] = sharedLib.getCircsAttrImmediateChildrenSummary(svgFileName, 'svg.xsd');
            pathsComponentAttrSummary[numEntries] = sharedLib.getPathsAttrImmediateChildrenSummary(svgFileName, 'svg.xsd');
            groupsComponentAttrSummary[numEntries] = sharedLib.getGroupsAttrImmediateChildrenSummary(svgFileName, 'svg.xsd');

            numEntries++;
          }
        })
      }

      res.send(
        {

          uploadStatus: sucessValue,
          names: retStr,
          entries: numEntries,
          sizes: fileSizes,
         

          numRectangle: numRects,
          numCircle: numCircles,
          numPath : numPaths,
          numGroup : numGroups,
          
          title : titles,

          actualTitle: actualTitles,
          desc: descriptors,

          rectsComponentSum : rectsComponentSummary,
          rectsAttrComponentSum: rectsComponentAttrSummary,

          circlesComponentSum : circlesComponentSummary,
          circlesAttrComponentSum : circlesComponentAttrSummary,

          pathsComponentSum : pathsComponentSummary,  
          pathsAttrComponentSummary : pathsComponentAttrSummary,
  
          groupsComponentSum : groupsComponentSummary,
          groupsComponentAttrSummary : groupsComponentAttrSummary

        }
      );
    })
});


app.get('/updateNameDescEndpoint', function (req, res) {

  let myNewName = req.query.name;
  let myNewDesc = req.query.desc;
  let fileName = 'uploads/' + req.query.fileName

  if (sharedLib.updateSVGNameDesc(fileName, 'svg.xsd', myNewName, myNewDesc) == false){
    console.log("updateSVGNameDesc Error");
  }

  res.send(
    {
      
    }
  );
});



app.get('/updateRectsScaleEndpoint', function (req, res) {

  let myNewScale = req.query.scale;
  let fileName = 'uploads/' + req.query.fileName

  if (sharedLib.scaleRect(fileName, 'svg.xsd', myNewScale) == false) {
    console.log("updateSVGNameDesc Error");
  }

  res.send(
    {

    }
  );
});



app.get('/updatecirclesScaleEndpoint', function (req, res) {

  let myNewScale = req.query.scale;
  let fileName = 'uploads/' + req.query.fileName

  if (sharedLib.scaleCirc(fileName, 'svg.xsd', myNewScale) == false) {
    console.log("updateSVGNameDesc Error");
  }

  res.send(
    {

    }
  );
});



app.get('/updatecirclesScaleEndpoint', function (req, res) {

  let myNewScale = req.query.scale;
  let fileName = 'uploads/' + req.query.fileName

  if (sharedLib.scaleCirc(fileName, 'svg.xsd', myNewScale) == false) {
    console.log("updateSVGNameDesc Error");
  }

  res.send(
    {

    }
  );
});


app.get('/addRectEndpoint', function (req, res) {

  let myX = req.query.newX;
  let myY = req.query.newY;
  let myWith = req.query.newWidth;
  let myHeight = req.query.newHeight;

  let fileName = 'uploads/' + req.query.fileName


  if (sharedLib.addRect(fileName, 'svg.xsd', myX, myY, myWith, myHeight) == false) {
    console.log("updateSVGNameDesc Error");
  }

  res.send(
    {

    }
  );
});


app.get('/addCircEndpoint', function (req, res) {

  let myX = req.query.newCX;
  let myY = req.query.newCY;
  let myR = req.query.newR;

  let fileName = 'uploads/' + req.query.fileName

  if (sharedLib.addCirc(fileName, 'svg.xsd', myX, myY, myR) == false) {
    console.log("updateSVGNameDesc Error");
  }

  res.send(
    {

    }
  );
});








app.listen(portNum);
console.log('Running app at localhost: ' + portNum);