#ifndef RemotlyControlled_h
#define RemotlyControlled_h

#include "Arduino.h"
#include "ControllerConnector.h"

/**
 * Any point or object that can be remotely controlled. Remote control means that object
 * can accept commands send by server or device different than Arduino board when program 
 * resists.  
 * 
 * Any remotely controlled object needs to have a name to be identified.
 */
class ObjectRemotelyControlled {

  protected:
    String name;
    ObjectRemotelyControlled *parent = NULL;
    ControllerConnector *controllerConnector = NULL;
    
  public:
    /**
     * Constructor to force giving a name to controlled objects.
     */
    ObjectRemotelyControlled(String _name) { this->name = _name;};
    
    /**
     * Virtual destructor to allow clean up for any children of this object.
     */
    virtual ~ObjectRemotelyControlled() {};

    /**
     * Set parent object to create hierarchy
     */
    void setParent(ObjectRemotelyControlled *_parent) {this->parent = _parent;} ;

    /**
     * Set connector for communication with controller.
     */
    void setControllerConnector(ControllerConnector *_controllerConnector) {this->controllerConnector = _controllerConnector;};

    /**
     * Gets name of top object in hierarchy described by full remote name.
     *
     * E.g.: for /Adr0/Room1/Point1 will result with Ard0
     */
    String getTopHierarchyName(String objectFullRemoteName);

    /**
     * Gets location of object with subtraction of top object in hierarchy described by full remote name.
     *
     * E.g.: for /Adr0/Room1/Point1 will result with /Room1/Point1
     */
    String getSublocation(String objectFullRemoteName);

    /**
     * Send update of current state to Controller
     */
    void sendStateUpdate();

    /**
     * Get name of object. Only local name will be returned without location in hierarchy.
     */
    virtual String getRemoteName();

    /**
     * Get full name of object including location in hierarchy. Name is created using
     * Unix like directory structure where delimiter '/' is used to separate objects.
     *
     * E.g. /Ard0/Room/Point
     *
     * @return Table where remote name was copied.
     */
    virtual String getFullRemoteName();

    /**
     * Create command which describes current state of object.
     * E.g. In case of {@link LightPoint} this will create command to set light in On/Off position
     * depending on current state.
     */
    virtual String createCommand() = 0;

    /**
     * Create comment to set required state of object.
     * E.g. If there is a need to set {@link LightPoint} into On state, appropriate parameter should
     * be provided.
     */
    virtual String createCommand(int state) = 0;

    /**
     * Execution of command on object. Function responsible to verify given object is object which should
     * respond to command (by object full name) and perform execution.
     */
    virtual void executeCommand(String objectFullRemoteName, String command) = 0;
 };

 #endif
