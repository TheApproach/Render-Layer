Approach provides a powerful and flexible way to create and manage content. With Approach for web, you can easily create and customize dynamic layouts, templates, and content using familiar HTML syntax. 

# Render-Layer
Sanctioned implementations of the Approach Render Layer
Welcome to Approach!


To create a layout or template with Approach, you'll need to use the Approach\Render\HTML class. This class provides a set of methods that allow you to build an HTML document using PHP.

Here's an example of how you might use the HTML class to create a simple layout:

```
  // Create an HTML object
  $html = new Approach\Render\HTML();
  
  // Add a head element
  $html->addHead('<title>My Website</title>');
  
  // Add a body element
  $html->addBody('<h1>Welcome to my website!</h1>');
  
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
    <h1>Welcome to my website!</h1>
  </body>
</html>
```

You can add any valid HTML content to the head or body elements using the addHead() and addBody() methods. You can also nest elements within each other to create more complex layouts.

First, let's create an instance of the HTML class, which represents an HTML element. We'll create the root html element:
```
  $html = new HTML('html');
```

Next, let's create the head element and add it to our html element:
```
$webpage->head = new HTML('head');
```

Inside the head element, let's add a title element:
```
$webpage->head->title = new HTML('title');
```

Now let's move on to the body element. We'll create an instance of the HTML class for the body element, and add it to our html element:
```
$body = $webpage->body = new HTML(tag: 'body', classes: [ 'no-margin','no-padding' ]);
```

Notice that we're using the tag and classes options to specify the tag name and CSS classes for the element. We can also add custom attributes to the element using the attributes option:
```
$body->attributes['data-attr']='special value';
```

That's it! You now know the basics of creating an HTML page using the Approach\Render\HTML class. You can continue building out your page by adding more elements and attributes as needed. When you're ready to render the page, just call the __toString method on your html element:

```
echo $webpage;
```


===

More generally, nodes are streaming list processors. The entrypoint function to a application, such as main(), has an ordered list of operations and branching subfunctions, creating the call stack. Similarly, Render Nodes and types that extend from always have both properties and a list of other nodes. By default this forms a DOM-like tree.


We want to represent format fragments as close to primitive data structures as possible. Render Nodes are designed to have their properties set directly by. The classes are designed to be extended and specialized as needed. Any input or output format may be represented efficiently as Node types. Nodes, in many ways, are analogs to I/O streams. 

For those familiar with pipes in traditional POSIX contexts, one could look at Nodes as hierarchies of typed pipes. For those familiar with web technologies, Nodes let you create a DOM of your own custom types. While we often use XML to illustrate, Nodes can represent anything from a simple wrapped string to complex binary formats.