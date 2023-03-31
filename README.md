Approach provides a powerful and flexible way to create and manage content. With Approach for web, you can easily create and customize dynamic layouts, templates, and content using familiar HTML syntax. 

# Render-Layer
Sanctioned implementations of the Approach Render Layer
Welcome to Approach!


To create a layout or template with Approach, you'll need to use the Approach\Render\HTML class. This class provides a set of methods that allow you to build an HTML document using PHP.

Here's an example of how you might use the HTML class to create a simple layout:

```
  // Create an HTML object
  $html = new Approach\Render\HTML(tag: 'html');
  
  // Add a head element
  $html[] = $head = new HTML( tag: 'head', content: '<title>Hello World</title>'); // you can still use string tags in content
  
  // Add a body element
  $html[] = $body = new HTML( tag: 'body' );
  $body[] = $main = new HTML( tag: 'div', classes: [ 'myClass' ]);

  $main->content = 'This is a web page';
  
  // Render the HTML document
  echo $html;
```


This will output the following HTML:
```
<html>
  <head>
    <title>My Website</title>
  </head>
  <body>
    <div class="myClass">Welcome to my website!</div>
  </body>
</html>
```

Notice that we're using the tag and classes options to specify the tag name and CSS classes for the element.
We can also change properties after construction:
```
$body->attributes['data-attr']='special value';
```

That's it! You now know the basics of creating an HTML page using the Approach\Render\HTML class. You can continue building out your page by adding more elements and attributes as needed. When you're ready to render the page, just echo or print_r your root node.


===

More generally, nodes are streaming list processors. The entrypoint function to a application, such as main(), has an ordered list of operations and branching subfunctions, creating the call stack. Similarly, Render Nodes and types that extend from Node always have both a paylod of public properties and a list of other nodes. By default this forms a DOM-like tree.


We want to represent format fragments as close to primitive data structures as possible. Render Nodes are designed to have their properties set directly by. The classes are designed to be extended and specialized as needed. Any input or output format may be represented efficiently as Node types. Nodes, in many ways, are analogs to I/O streams. 

For those familiar with pipes in traditional POSIX contexts, one could look at Nodes as hierarchies of typed pipes. For those familiar with web technologies, Nodes let you create a DOM of your own custom types. While we often use XML to illustrate, Nodes can represent anything from a simple wrapped string to complex binary formats.
